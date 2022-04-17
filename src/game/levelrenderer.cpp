
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
                lines.emplace_back(std::make_pair(
                    pt - Vect2f{0, 10.0f},
                    Vect2f{pt.x * 1.8f, pt.y}
                ));

            break;
    }

    return lines;
}

Line2f LevelRenderer::normalizeLine(Line2f line) const
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

// TO DO : pass a type to Enemy Base Point
std::vector<Line2f> EnemyBasePoint(EnemyShape type)
{
    std::vector<Line2f> lines;
    switch (type)
    {
    case SQUARE_MIDDLE:
        lines = {
            std::make_pair(Engine::Vect2f{0.40, 0},   Engine::Vect2f{0.6, 0}),
            std::make_pair(Engine::Vect2f{0.6,  0},   Engine::Vect2f{0.6, 0.1}),
            std::make_pair(Engine::Vect2f{0.6,  0.1}, Engine::Vect2f{0.4, 0.1}),
            std::make_pair(Engine::Vect2f{0.4,  0.1}, Engine::Vect2f{0.4, 0})
        };
        break;
    
    default:
        break;
    }
    return lines;
}

void LevelRenderer::drawEnemy(const Output& out, const Enemy& e) const
{
    assert(e.line() < m_lines.size());
    /**
     * @brief put the enemy in the good position in U space
     */
    std::pair<Line2f, Line2f> llines = laneLines(e.line());
    Line2f top = std::make_pair<Vect2f, Vect2f>(
        laneLines(e.line()).first.second,
        laneLines(e.line()).second.second
    );
    Vect2f U{top.first, top.second};
    Vect2f middle = Vect2f::center(llines.first.first, llines.second.first); 

    // put each point and normalized it to U
    std::vector<Line2f> lines{EnemyBasePoint(e.type())};
    for (Line2f& line : lines)
    {
        line.first.putInU(U, top.first);
        line.second.putInU(U, top.first);
    }

    /** 
     * @brief now move by homothetie 
    */
    for(Line2f& line : lines)
    {
        float z, h;
        z = e.position()/100;
        h = z*z;
        line.first = Vect2f::homothetie(h, line.first, middle);
        line.second = Vect2f::homothetie(h, line.second, middle);
    }

    out.setColor(Enemy::ENEMY_COLOR);
    for(Line2f& line : lines)
    {
        out.drawLine(line);
    }
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
