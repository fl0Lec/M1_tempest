#include "player.hpp"

#include "color.hpp"
#include "geometry.hpp"
#include "keycode.hpp"
#include "levelrenderer.hpp"
#include "vect2.hpp"

#include <utility>

using namespace Engine;

Player::Player(const std::shared_ptr<LevelRenderer>& level)
    : Entity{0, 100}, m_level{level}
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
    const std::pair<Line2f, Line2f> lanes = m_level->laneLines(m_line);

    const Vect2f fromCenter
        = Vect2f::middle(lanes.first.second, lanes.second.second)
        - Vect2f::middle(lanes.first.first, lanes.second.first);

    const Vect2f end = Vect2f::middle(lanes.first.second, lanes.second.second);

    // TODO adapt drawing to have 90 degrees angle, and not directly attached to line
    out.setColor(Color::YELLOW);
    out.drawLine(lanes.first.second, end + fromCenter * 0.3f);
    out.drawLine(lanes.second.second, end + fromCenter * 0.3f);
}
