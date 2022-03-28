
#include "enemy.hpp"

Enemy::Enemy(uint line, double speed, EnemyShape type)
    :Entity(line), m_speed(speed), m_type(type) {}


EnemyShape Enemy::getType() const 
{
    return m_type;
}

bool Enemy::asReachEnd() const 
{
    return getPosition()>100;
}

void Enemy::update (const Engine::Input &in)
{
    m_position+=m_speed;
}