
#include "levelrenderer.hpp"

#include <utility>
#include <vector>
#include <cassert>
#include <iostream>

#include "color.hpp"
#include "enemy.hpp"
#include "game.hpp"
#include "input.hpp"
#include "output.hpp"
#include "vect2.hpp"

using namespace Engine;

const Color LevelRenderer::DEFAULT_COLOR = Color::BLUE;
const Color LevelRenderer::PLAYER_COLOR  = Color::YELLOW;

static const std::vector<Vect2f> baseTriangle{
    Vect2f{-1.75, -2},
    Vect2f{-1.75, -1},
    Vect2f{-1.25, -1},
    Vect2f{-1.25,  0},
    Vect2f{-0.75,  0},
    Vect2f{-0.75,  1},
    Vect2f{-0.25,  1},
    Vect2f{-0.25,  2},
    Vect2f{ 0.25,  2},
    Vect2f{ 0.25,  1},
    Vect2f{ 0.75,  1},
    Vect2f{ 0.75,  0},
    Vect2f{ 1.25,  0},
    Vect2f{ 1.25,  -1},
    Vect2f{ 1.75,  -1},
    Vect2f{ 1.75,  -2}
};

static const std::vector<Vect2f> baseCircle{
    Vect2f{ 0,      -1},
    Vect2f{-0.4375, -0.9375},
    Vect2f{-0.75,   -0.75},
    Vect2f{-0.9375, -0.4375},
    Vect2f{-1,       0},
    Vect2f{-0.9375,  0.4375},
    Vect2f{-0.75,    0.75},
    Vect2f{-0.4375,  0.9375},
    Vect2f{ 0,       1},
    Vect2f{ 0.4375,  0.9375},
    Vect2f{ 0.75,    0.75},
    Vect2f{ 0.9375,  0.4375},
    Vect2f{ 1,       0},
    Vect2f{ 0.9375, -0.4375},
    Vect2f{ 0.75,   -0.75},
    Vect2f{ 0.4375, -0.9375},
    Vect2f{ 0,      -1}
};

static const std::vector<float> baseFlat{
    -1,
    -0.875,
    -0.75,
    -0.625,
    -0.5,
    -0.375,
    -0.25,
    -0.125,
     0,
     0.125,
     0.25,
     0.375,
     0.5,
     0.625,
     0.75,
     0.875,
     1
};

static const std::vector<Vect2f> baseStar{
    Vect2f{ 0,      -0.75},
    Vect2f{-0.375,  -1},
    Vect2f{-0.5625, -0.5625},
    Vect2f{-1,      -0.375},
    Vect2f{-0.75,    0},
    Vect2f{-1,       0.375},
    Vect2f{-0.5625,  0.5625},
    Vect2f{-0.375,   1},
    Vect2f{ 0,       0.75},
    Vect2f{ 0.375,   1},
    Vect2f{ 0.5625,  0.5625},
    Vect2f{ 1,       0.375},
    Vect2f{ 0.75,    0},
    Vect2f{ 1,      -0.375},
    Vect2f{ 0.5625, -0.5625},
    Vect2f{ 0.375,  -1},
    Vect2f{ 0,      -0.75}
};

std::vector<Line2f> LevelRenderer::levelBasePoints(LevelType type)
{
    std::vector<Line2f> lines;

    switch(type)
    {
        case PLUS:
            lines = std::vector<std::pair<Vect2f, Vect2f>>{
                std::make_pair(Vect2f{ 0,    1},   Vect2f{ 0,  2}),
                std::make_pair(Vect2f{ 0.5,  1},   Vect2f{ 1,  2}),
                std::make_pair(Vect2f{ 0.5,  0.5}, Vect2f{ 1,  1}),
                std::make_pair(Vect2f{ 1,    0.5}, Vect2f{ 2,  1}),
                std::make_pair(Vect2f{ 1,    0},   Vect2f{ 2,  0}),
                std::make_pair(Vect2f{ 1,   -0.5}, Vect2f{ 2, -1}),
                std::make_pair(Vect2f{ 0.5, -0.5}, Vect2f{ 1, -1}),
                std::make_pair(Vect2f{ 0.5, -1},   Vect2f{ 1, -2}),
                std::make_pair(Vect2f{ 0,   -1},   Vect2f{ 0, -2}),
                std::make_pair(Vect2f{-0.5, -1},   Vect2f{-1, -2}),
                std::make_pair(Vect2f{-0.5, -0.5}, Vect2f{-1, -1}),
                std::make_pair(Vect2f{-1,   -0.5}, Vect2f{-2, -1}),
                std::make_pair(Vect2f{-1,    0},   Vect2f{-2,  0}),
                std::make_pair(Vect2f{-1,    0.5}, Vect2f{-2,  1}),
                std::make_pair(Vect2f{-0.5,  0.5}, Vect2f{-1,  1}),
                std::make_pair(Vect2f{-0.5,  1},   Vect2f{-1,  2}),
                std::make_pair(Vect2f{ 0,    1},   Vect2f{ 0,  2})
            };
            for(auto& line : lines)
            {
                line.first += Vect2f{0, 1.5};
                line.first *= 3.0f;
            }
            break;
        
        case SQUARE:
            lines = std::vector<std::pair<Vect2f, Vect2f>>{
                std::make_pair(Vect2f{ 0,    1},    Vect2f{ 0,  2}),
                std::make_pair(Vect2f{ 0.25, 1},    Vect2f{ 1,  2}),
                std::make_pair(Vect2f{ 0.5,  1},    Vect2f{ 2,  2}),
                std::make_pair(Vect2f{ 0.5,  0.75}, Vect2f{ 2,  1}),
                std::make_pair(Vect2f{ 0.5,  0.5},  Vect2f{ 2,  0}),
                std::make_pair(Vect2f{ 0.5,  0.25}, Vect2f{ 2, -1}),
                std::make_pair(Vect2f{ 0.5,  0},    Vect2f{ 2, -2}),
                std::make_pair(Vect2f{ 0.25, 0},    Vect2f{ 1, -2}),
                std::make_pair(Vect2f{ 0,    0},    Vect2f{ 0, -2}),
                std::make_pair(Vect2f{-0.25, 0},    Vect2f{-1, -2}),
                std::make_pair(Vect2f{-0.5,  0},    Vect2f{-2, -2}),
                std::make_pair(Vect2f{-0.5,  0.25}, Vect2f{-2, -1}),
                std::make_pair(Vect2f{-0.5,  0.5},  Vect2f{-2,  0}),
                std::make_pair(Vect2f{-0.5,  0.75}, Vect2f{-2,  1}),
                std::make_pair(Vect2f{-0.5,  1},    Vect2f{-2,  2}),
                std::make_pair(Vect2f{-0.25, 1},    Vect2f{-1,  2}),
                std::make_pair(Vect2f{ 0,    1},    Vect2f{ 0,  2})
            };
            for(auto& line : lines)
            {
                line.first += Vect2f{0, 1.5};
                line.first *= 4.0f;
            }
            break;

        case TRIANGLE:
            for(const auto& pt : baseTriangle)
                lines.emplace_back(std::make_pair(
                    pt - Vect2f{0, 10.0f},
                    Vect2f{pt.x * 1.8f, pt.y}
                ));
            break;

        case CIRCLE:
            for(const auto& pt : baseCircle)
                lines.emplace_back(std::make_pair(
                    pt + Vect2f{0, 8.0f},
                    Vect2f{pt.x * 1.6f, pt.y * 1.9f}
                ));
            break;

        case FLAT:
            for(const auto& val : baseFlat)
                lines.emplace_back(std::make_pair(
                    Vect2f{val * 1.5f, -12.0f},
                    Vect2f{val * 2.5f, 1.7f}
                ));
            break;

        case STAR:
            for(const auto& pt : baseStar)
                lines.emplace_back(std::make_pair(
                    (pt + Vect2f{0, 3.0f}) * 1.2f,
                    Vect2f{pt.x * 1.6f, pt.y * 1.9f}
                ));
            break;
    }

    return lines;
}

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
    const auto points = levelBasePoints(type);
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
