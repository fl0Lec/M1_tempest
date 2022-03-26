
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
        case PLUS:
            points = std::vector<std::pair<Vect2f, Vect2f>>{
                std::make_pair(Vect2f{ 0,    1},   Vect2f{ 0,  2}),
                std::make_pair(Vect2f{-0.5,  1},   Vect2f{-1,  2}),
                std::make_pair(Vect2f{-0.5,  0.5}, Vect2f{-1,  1}),
                std::make_pair(Vect2f{-1,    0.5}, Vect2f{-2,  1}),
                std::make_pair(Vect2f{-1,    0},   Vect2f{-2,  0}),
                std::make_pair(Vect2f{-1,   -0.5}, Vect2f{-2, -1}),
                std::make_pair(Vect2f{-0.5, -0.5}, Vect2f{-1, -1}),
                std::make_pair(Vect2f{-0.5, -1},   Vect2f{-1, -2}),
                std::make_pair(Vect2f{ 0,   -1},   Vect2f{ 0, -2}),
                std::make_pair(Vect2f{ 0.5, -1},   Vect2f{ 1, -2}),
                std::make_pair(Vect2f{ 0.5, -0.5}, Vect2f{ 1, -1}),
                std::make_pair(Vect2f{ 1,   -0.5}, Vect2f{ 2, -1}),
                std::make_pair(Vect2f{ 1,    0},   Vect2f{ 2,  0}),
                std::make_pair(Vect2f{ 1,    0.5}, Vect2f{ 2,  1}),
                std::make_pair(Vect2f{ 0.5,  0.5}, Vect2f{ 1,  1}),
                std::make_pair(Vect2f{ 0.5,  1},   Vect2f{ 1,  2}),
                std::make_pair(Vect2f{ 0,    1},   Vect2f{ 0,  2})
            };
            for(auto& line : points)
            {
                line.first += Vect2f{0, 1.5};
                line.first *= 3.0f;
            }
            break;
        
        case SQUARE:
            points = std::vector<std::pair<Vect2f, Vect2f>>{
                std::make_pair(Vect2f{ 0,    1},    Vect2f{ 0,  2}),
                std::make_pair(Vect2f{-0.25, 1},    Vect2f{-1,  2}),
                std::make_pair(Vect2f{-0.5,  1},    Vect2f{-2,  2}),
                std::make_pair(Vect2f{-0.5,  0.75}, Vect2f{-2,  1}),
                std::make_pair(Vect2f{-0.5,  0.5},  Vect2f{-2,  0}),
                std::make_pair(Vect2f{-0.5,  0.25}, Vect2f{-2,  -1}),
                std::make_pair(Vect2f{-0.5,   0},    Vect2f{-2,  -2}),
                std::make_pair(Vect2f{-0.25,  0},    Vect2f{-1, -2}),
                std::make_pair(Vect2f{ 0,     0},    Vect2f{ 0, -2}),
                std::make_pair(Vect2f{ 0.25,  0},    Vect2f{ 1, -2}),
                std::make_pair(Vect2f{ 0.5,   0},    Vect2f{ 2, -2}),
                std::make_pair(Vect2f{ 0.5,  0.25}, Vect2f{ 2, -1}),
                std::make_pair(Vect2f{ 0.5,  0.5},  Vect2f{ 2, 0}),
                std::make_pair(Vect2f{ 0.5,  0.75}, Vect2f{ 2, 1}),
                std::make_pair(Vect2f{ 0.5,  1},    Vect2f{ 2, 2}),
                std::make_pair(Vect2f{ 0.25,  1},   Vect2f{ 1,  2}),
                std::make_pair(Vect2f{ 0,    1},    Vect2f{ 0,  2})
            };
            for(auto& line : points)
            {
                line.first += Vect2f{0, 1.5};
                line.first *= 4.0f;
            }
            break;

        case TRIANGLE:
            std::vector<Vect2f> base{
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
            for(const auto& pt : base)
                points.emplace_back(std::make_pair(
                    pt - Vect2f{0, 10.0f},
                    Vect2f{pt.x * 1.8f, pt.y}
                ));

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
    m_laneCount = points.size() - 1;

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

size_t LevelRenderer::laneCount() const
{
    return m_laneCount;
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
