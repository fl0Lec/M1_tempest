
#include "levelrenderer.hpp"

#include <utility>
#include <vector>

#include "color.hpp"
#include "game.hpp"
#include "input.hpp"
#include "vect2.hpp"

using namespace Engine;

const Color LevelRenderer::DEFAULT_COLOR = Color::BLUE;
const Color LevelRenderer::PLAYER_COLOR = Color::YELLOW;

std::vector<std::pair<Vect2f, Vect2f>>
    LevelRenderer::levelBasePoints(LevelType type)
{
    std::vector<std::pair<Vect2f, Vect2f>> points;

    switch(type)
    {
        case SQUARE:
            points.emplace_back(std::make_pair(Vect2f{-1, 1},  Vect2f{-2, 2}));
            points.emplace_back(std::make_pair(Vect2f{-1, 0},  Vect2f{-2, 0}));
            points.emplace_back(std::make_pair(Vect2f{-1, -1}, Vect2f{-2, -2}));
            points.emplace_back(std::make_pair(Vect2f{0, -1},  Vect2f{0, -2}));
            points.emplace_back(std::make_pair(Vect2f{1, -1},  Vect2f{2, -2}));
            points.emplace_back(std::make_pair(Vect2f{1, 0},   Vect2f{2, 0}));
            points.emplace_back(std::make_pair(Vect2f{1, 1},   Vect2f{2, 2}));
            points.emplace_back(std::make_pair(Vect2f{0, 1},   Vect2f{0, 2}));
            points.emplace_back(std::make_pair(Vect2f{-1, 1},  Vect2f{-2, 2}));
            break;
    }

    return points;
}

std::pair<Vect2f, Vect2f> LevelRenderer::normalizeLine(
    std::pair<Vect2f, Vect2f> line)
{
    const size_t height = Game::instance()->height() / 2;

    line.first = m_center + line.first * (height * CENTER_SIZE);
    line.second = m_center + line.second / 2.0f * (height * (CENTER_SIZE + LANE_SIZE));

    return line;
}

LevelRenderer::LevelRenderer(const Vect2f& center, LevelType type)
    : m_type(type), m_center(center)
{
    const auto points = levelBasePoints(type);

    std::pair<Vect2f, Vect2f> last = normalizeLine(points.front());
    m_lines.emplace_back(last);

    for(auto it = ++points.cbegin(); it != points.cend(); ++it)
    {
        const std::pair<Vect2f, Vect2f> line = normalizeLine(*it);

        m_lines.emplace_back(line);
        m_lines.emplace_back(std::make_pair(line.first, last.first));
        m_lines.emplace_back(std::make_pair(line.second, last.second));

        last = line;
    }
}

void LevelRenderer::render(const Output &out) const
{
    out.setColor(DEFAULT_COLOR);

    for(const auto& line : m_lines)
    {
        out.drawLine(line.first, line.second);
    }
}

void LevelRenderer::update([[maybe_unused]] const Input &in)
{ }
