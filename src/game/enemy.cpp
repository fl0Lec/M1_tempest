
#include "enemy.hpp"

#include "levelrenderer.hpp"

using namespace Engine;

const Engine::Color Enemy::ENEMY_COLOR = Engine::Color::RED;

Enemy::Enemy(uint line, double speed, EnemyShape type,
    const LevelRenderer& level)
    : Entity{line, 0}, m_speed(speed), m_type(type), m_level(level)
{}

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
}

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

    out.setColor(Enemy::ENEMY_COLOR);
    for(Line2f& line : lines)
    {
        out.drawLine(line);
    }
}
