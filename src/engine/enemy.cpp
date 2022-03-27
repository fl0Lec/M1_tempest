
#include "enemy.hpp"

Enemy::Enemy(uint line, double speed, Engine::EnemyShape type)
    :Entity(line), m_speed(speed), m_type(type) {}


Engine::EnemyShape Enemy::getType() const 
{
    return m_type;
}

bool Enemy::asReachEnd() const 
{
    return getPosition()>100;
}
