
#include "enemy.hpp"

#include "color.hpp"
#include "levelrenderer.hpp"

#include <cstdlib>

using namespace Engine;

Enemy::Enemy(uint line, EnemyShape type,
    const LevelRenderer& level)
    : Entity{line, 0}, m_changeLane(0), m_type(type), m_level(level)
{
    switch (type)
    {
    case SQUARE_MIDDLE:
        m_speed = 0.2;
        break;
    default:
        m_speed = 0.5;
        break;
    }
}

EnemyShape Enemy::type() const 
{
    return m_type;
}

bool Enemy::asReachEnd() const 
{
    return position() >= 100;
}

unsigned int Enemy::givenScore() const
{
    return GIVEN_SCORE;
}

void Enemy::update([[maybe_unused]] const Input &in)
{
    m_position += m_speed;
    if (m_type==FLIPPER)
    {
        if ((++m_changeLane>50) && (std::rand()%200-m_changeLane<0))
            {
                m_changeLane=0;
                m_line= (m_line+(std::rand()%2?1:-1)) % m_level.laneCount();
            }

    }
}

std::vector<Line2f> EnemyBasePoint(EnemyShape type)
{
    std::vector<Line2f> lines;
    switch (type)
    {
    case SQUARE_MIDDLE:
        lines = {
            std::make_pair(Engine::Vect2f{0.40, 0},   Engine::Vect2f{0.6, 0}),
            std::make_pair(Engine::Vect2f{0.6,  0},   Engine::Vect2f{0.6, -0.1}),
            std::make_pair(Engine::Vect2f{0.6,  -0.1}, Engine::Vect2f{0.4, -0.1}),
            std::make_pair(Engine::Vect2f{0.4,  -0.1}, Engine::Vect2f{0.4, 0})
        };
        break;
    case FLIPPER :
        lines = {
            std::make_pair(Engine::Vect2f{0,0}, Engine::Vect2f{0.15,-0.15}),
            std::make_pair(Engine::Vect2f{0.15,-0.15}, Engine::Vect2f{0,-0.3}),
            std::make_pair(Engine::Vect2f{0,-0.3}, Engine::Vect2f{0.5, -0.2}),
            std::make_pair(Engine::Vect2f{0.5, -0.2}, Engine::Vect2f{1,-0.3}),
            std::make_pair(Engine::Vect2f{1,-0.3}, Engine::Vect2f{0.85,-0.15}),
            std::make_pair(Engine::Vect2f{0.85,-0.15}, Engine::Vect2f{1,0}),
            std::make_pair(Engine::Vect2f{1,0}, Engine::Vect2f{0.5,-0.2}),
            std::make_pair(Engine::Vect2f{0.5,-0.2}, Engine::Vect2f{0,0}),
        };
        break;
    case SPIKER :
        lines = {
            std::make_pair(Engine::Vect2f{0.3, -0.062}, Engine::Vect2f{0.3,-0.165}),
            std::make_pair(Engine::Vect2f{0.3, -0.165}, Engine::Vect2f{0.324, -0.269}),
            std::make_pair(Engine::Vect2f{0.324, -0.269}, Engine::Vect2f{0.417,-0.35}),
            std::make_pair(Engine::Vect2f{0.417, -0.35}, Engine::Vect2f{0.53, -0.392}),
            std::make_pair(Engine::Vect2f{0.53, -0.392}, Engine::Vect2f{0.65, -0.312}),
            std::make_pair(Engine::Vect2f{0.65, -0.312}, Engine::Vect2f{0.72, -0.222}),
            std::make_pair(Engine::Vect2f{0.72, -0.222}, Engine::Vect2f{0.718, -0.113}),
            std::make_pair(Engine::Vect2f{0.718, -0.113}, Engine::Vect2f{0.646, -0.043}),
            std::make_pair(Engine::Vect2f{0.646, -0.043}, Engine::Vect2f{0.525, 0}),
            std::make_pair(Engine::Vect2f{0.525, 0}, Engine::Vect2f{0.42, -0.06}),
            std::make_pair(Engine::Vect2f{0.42, -0.06}, Engine::Vect2f{0.39, -0.18}),
            std::make_pair(Engine::Vect2f{0.39, -0.18}, Engine::Vect2f{0.44, -0.279}),
            std::make_pair(Engine::Vect2f{0.44, -0.279}, Engine::Vect2f{0.57, -0.279}),
            std::make_pair(Engine::Vect2f{0.57, -0.279}, Engine::Vect2f{0.637, -0.156}),
            std::make_pair(Engine::Vect2f{0.637, -0.156}, Engine::Vect2f{0.53, -0.092}),
            std::make_pair(Engine::Vect2f{0.53, -0.092}, Engine::Vect2f{0.47, -0.147})
        };
        for (auto &line : lines) {
            line.first*=0.8;
            line.second*=0.8;
            
        }
        break;
    default:
        break;
    }
    return lines;
}

void Enemy::render(const Output &out) const
{
    /**
     * @brief put the enemy in the good position in U space
     */
    std::pair<Line2f, Line2f> llines = m_level.laneLines(m_line);
    Line2f top = std::make_pair<Vect2f, Vect2f>(
        m_level.laneLines(m_line).first.second,
        m_level.laneLines(m_line).second.second
    );
    Vect2f U{top.first, top.second};
    Vect2f middle = Vect2f::center(llines.first.first, llines.second.first); 

    // put each point and normalized it to U
    std::vector<Line2f> lines{EnemyBasePoint(m_type)};
    for (Line2f& line : lines)
    {
        line.first.putInU(U, top.first);
        line.second.putInU(U, top.first);
    }

    /** 
     * @brief now move by homothetie 
    */
    float h = (m_position/100)* (m_position/100);
    for(Line2f& line : lines)
    {
        line.first = Vect2f::homothetie(h, line.first, middle);
        line.second = Vect2f::homothetie(h, line.second, middle);
    }

    out.setColor(enemyColor(m_type));
    for(Line2f& line : lines)
    {
        out.drawLine(line);
    }
}

Color Enemy::enemyColor(EnemyShape s)
{
    switch(s)
    {
        case SQUARE_MIDDLE:
            return Color::MAGENTA;
        case FLIPPER:
            return Color::RED;
        case SPIKER:
            return Color::GREEN;
        default :
            return Color::BLACK;
    }
}
