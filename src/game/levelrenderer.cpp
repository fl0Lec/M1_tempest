
#include "levelrenderer.hpp"

#include <utility>
#include <vector>
#include <cassert>

#include "color.hpp"
#include "game.hpp"
#include "input.hpp"
#include "vect2.hpp"


#include <iostream>
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
            for(auto& line : lines)
            {
                line.first += Vect2f{0, 1.5};
                line.first *= 3.0f;
            }
            break;
        
        case SQUARE:
            lines = std::vector<std::pair<Vect2f, Vect2f>>{
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

Line2f LevelRenderer::normalizeLine(Line2f line)
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
        m_lines.emplace_back(std::make_pair(line.first, last.first));
        m_lines.emplace_back(std::make_pair(line.second, last.second));

        last = line;
    }
}

std::pair<Line2f, Line2f> LevelRenderer::laneLines(size_t lane)
{
    lane %= m_lines.size() - 1;

    return std::make_pair(m_lines[lane], m_lines[lane+1]);
}

size_t LevelRenderer::laneCount() const
{
    return m_laneCount;
}

// TO DO : pass a type to Enemy Base Point
std::vector<Line2f> EnemyBasePoint(EnemyShape type)
{
    std::vector<Line2f> lines;
    switch (type)
    {
    case SQUARE_MIDDLE:
        lines = {
        std::make_pair(Engine::Vect2f{0.40, 0}, Engine::Vect2f{0.6,   0}),
        std::make_pair(Engine::Vect2f{0.6,  0}, Engine::Vect2f{0.6,    0.1}),
        std::make_pair(Engine::Vect2f{0.6, 0.1},   Engine::Vect2f{0.4, 0.1}),
        std::make_pair(Engine::Vect2f{0.4, 0.1},  Engine::Vect2f{0.4 , 0})
        };
        break;
    
    default:
        break;
    }
    return lines;
}

void LevelRenderer::drawEnemy(std::shared_ptr<Enemy> e)
{
    assert(e->getLine()<m_lines.size());
    std::pair<Line2f, Line2f> llines = laneLines(e->getLine());
    Line2f  top = std::make_pair<Vect2f, Vect2f>(laneLines(e->getLine()).first.second, laneLines(e->getLine()).second.second);
    Vect2f U = vectorized(top), middle = (llines.first.first+llines.second.first)/(float)2; 

    /** @brief put each point and normalized it to U */
    std::shared_ptr<std::vector<Line2f>> lines;
    lines = std::make_shared<std::vector<Line2f>>(EnemyBasePoint(e->getType()));
    for (Line2f& line : *lines)
    {
        putinU(line.first, U, top.first);
        putinU(line.second, U, top.first);
    }

    /** @brief now move by homothetie 
     * for now just move it linearly
     * later fast on out than in
    */
    for (Line2f& line : *lines)
    {
        float z, h;
        z = e->getPosition()/100;
        h = z*z;
        homothetie(line.first, h, middle);
        homothetie(line.second, h, middle);
    }
    m_enemy_lines.emplace_back(lines);
}

void LevelRenderer::clearEnemy()
{
    m_enemy_lines.clear();
}

void LevelRenderer::render(const Output &out) const
{
    out.setColor(DEFAULT_COLOR);

    for(const auto& line : m_lines)
    {
        out.drawLine(line.first, line.second);
    }
    out.setColor(Color::RED);
    for (const auto& enemy : m_enemy_lines)
    {
        for (const auto& line : *enemy)
        {
            out.drawLine(line.first, line.second);
        }
    }
}

void LevelRenderer::update([[maybe_unused]] const Input &in)
{ }

/**
 * @brief create geometrical vector from line
 */
Vect2f vectorized(Line2f l)
{
    return Vect2f{l.second.x-l.first.x, l.second.y-l.first.y};
}

/**
 * @brief modify directly p to put in the U.V space
 * V is orthogoanl to U and same length
 */
void putinU(Vect2f& p, const Vect2f& U, const Vect2f& A)
{
    Vect2f newp{p};
    newp.x = U.x*p.x - U.y*p.y + A.x;
    newp.y = U.y*p.x + U.x*p.y + A.y;
    p = newp;
}
void LevelRenderer::homothetie(Vect2f& P, double h, const Vect2f& center)
{
    Vect2f CP = P-center;
    P = center+CP*(float)h;

}