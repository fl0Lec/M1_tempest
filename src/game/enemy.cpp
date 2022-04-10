
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

void Enemy::render(const Output &out) const
{
    m_level.drawEnemy(out, *this);
}
