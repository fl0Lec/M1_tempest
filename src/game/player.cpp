#include "player.hpp"

#include "keycode.hpp"

using namespace Engine;

Player::Player(const std::shared_ptr<LevelRenderer>& level)
    : Entity(0, 200), m_level(level)
{ }

void Player::update(const Engine::Input &in)
{
    if(m_moveCooldown > 0)
        m_moveCooldown -= 1;
    
    if(m_moveCooldown <= 0
        && (in.isKeyPressed(Engine::KEY_Q) || in.isKeyPressed(Engine::KEY_LEFT)))
    {
        if(m_currentLane == 0)
            m_currentLane = m_level->laneCount() - 1;
        else
            m_currentLane -= 1;

        m_level->setPlayerLane(m_currentLane % m_level->laneCount());
        m_moveCooldown = MOVE_COOLDOWN;
    }
    else if(m_moveCooldown <= 0
        && (in.isKeyPressed(Engine::KEY_D) || in.isKeyPressed(Engine::KEY_RIGHT)))
    {
        m_currentLane += 1;

        m_level->setPlayerLane(m_currentLane % m_level->laneCount());
        m_moveCooldown = MOVE_COOLDOWN;
    }
}
