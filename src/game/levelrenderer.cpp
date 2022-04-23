
#include "levelrenderer.hpp"

#include <utility>
#include <vector>
#include <cassert>
#include <iostream>

#include "color.hpp"
#include "enemy.hpp"
#include "game.hpp"
#include "input.hpp"
#include "levels.hpp"
#include "output.hpp"
#include "vect2.hpp"

using namespace Engine;

const Color LevelRenderer::DEFAULT_COLOR = Color::BLUE;
const Color LevelRenderer::PLAYER_COLOR  = Color::YELLOW;


Line2f LevelRenderer::normalizeLine(Line2f line) const
{
    const size_t height = m_size / 2;

    line.first = m_center + line.first * (height * CENTER_SIZE);
    line.second = m_center + line.second / 2.0f * (height * (CENTER_SIZE + LANE_SIZE));

    return line;
}

LevelRenderer::LevelRenderer(const Vect2f& center, size_t size, LevelType type)
    : m_type(type), m_center(center), m_size(size)
{
    const auto points = Level::levelBasePoints(type);
    m_laneCount = points.size() - 1;

    Line2f last = normalizeLine(points.front());
    m_lines.emplace_back(last);

    for(auto it = ++points.cbegin(); it != points.cend(); ++it)
    {
        const Line2f line = normalizeLine(*it);

        m_lines.emplace_back(line);
        m_endLines.emplace_back(std::make_pair(line.first, last.first));
        m_endLines.emplace_back(std::make_pair(line.second, last.second));

        last = line;
    }

    setPlayerLane(0);
}

std::pair<Line2f, Line2f> LevelRenderer::laneLines(size_t lane) const
{
    lane %= m_lines.size() - 1;

    return std::make_pair(m_lines[lane], m_lines[lane+1]);
}

size_t LevelRenderer::laneCount() const
{
    return m_laneCount;
}

void LevelRenderer::setPlayerLane(size_t lane)
{
    std::pair<Line2f, Line2f> selectedLines = laneLines(lane);

    m_selectedLines.clear();
    m_selectedLines.emplace_back(selectedLines.first);
    m_selectedLines.emplace_back(selectedLines.second);

    m_selectedLines.emplace_back(std::make_pair(
        selectedLines.first.first, selectedLines.second.first)
    );
    m_selectedLines.emplace_back(std::make_pair(
        selectedLines.first.second, selectedLines.second.second)
    );
}

void LevelRenderer::render(const Output &out) const
{
    out.setColor(DEFAULT_COLOR);
    for(const auto& line : m_lines)
    {
        out.drawLine(line);
    }
    for(const auto& line : m_endLines)
    {
        out.drawLine(line);
    }

    out.setColor(PLAYER_COLOR);
    for(const auto& line : m_selectedLines)
    {
        out.drawLine(line);
    }
}

void LevelRenderer::update([[maybe_unused]] const Input &in)
{ }
