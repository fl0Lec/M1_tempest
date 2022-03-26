
#include "enemy.hpp"

Enemy::Enemy(uint line, double speed, Engine::EnemyShape type)
    :m_line(line), m_position(0), m_speed(speed), m_type(type) {}

uint Enemy::getLine() const 
{
    return m_line;
}

void Enemy::setLine(uint newLine)
{
    m_line = newLine;
}

double Enemy::getPosition() const
{
    return m_position;
}

Engine::EnemyShape Enemy::getType() const 
{
    return m_type;
}

bool Enemy::asReachEnd() const 
{
    return m_position>100;
}

void Enemy::update(const Engine::Input &in)
{
    m_position = (m_position+m_speed>100?200:m_position+m_speed);
}