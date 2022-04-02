#include "player.hpp"

#include "keycode.hpp"

using namespace Engine;

Player::Player(const std::shared_ptr<LevelRenderer>& level)
    : Entity(0, 100), m_level(level)
{ }

void Player::update(const Engine::Input &in)
{
    if(m_moveCooldown > 0)
        m_moveCooldown -= 1;
    
    if(m_moveCooldown <= 0
        && (in.isKeyPressed(Engine::KEY_Q) || in.isKeyPressed(Engine::KEY_LEFT)))
    {
        if(m_line == 0)
            m_line = m_level->laneCount() - 1;
        else
            m_line -= 1;

        m_level->setPlayerLane(m_line % m_level->laneCount());
        m_moveCooldown = MOVE_COOLDOWN;
    }
    else if(m_moveCooldown <= 0
        && (in.isKeyPressed(Engine::KEY_D) || in.isKeyPressed(Engine::KEY_RIGHT)))
    {
        m_line += 1;

        m_level->setPlayerLane(m_line % m_level->laneCount());
        m_moveCooldown = MOVE_COOLDOWN;
    }
}

void Player::render(const Output &out) const
{
    // TODO
}
