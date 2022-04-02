
#include "enemy.hpp"

using namespace Engine;

Enemy::Enemy(uint line, double speed, EnemyShape type)
    : Entity(line, 0), m_speed(speed), m_type(type)
{}

EnemyShape Enemy::type() const 
{
    return m_type;
}

bool Enemy::asReachEnd() const 
{
    return position() >= 100;
}

void Enemy::update(const Input &in)
{
    m_position += m_speed;
}

void Enemy::render(const Output &out) const
{
    // TODO
}
