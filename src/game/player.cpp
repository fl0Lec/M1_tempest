#include "player.hpp"

#include <memory>
#include <utility>

#include "color.hpp"
#include "geometry.hpp"
#include "gamescene.hpp"
#include "keycode.hpp"
#include "levelrenderer.hpp"
#include "missile.hpp"
#include "vect2.hpp"

using namespace Engine;

Player::Player(const std::shared_ptr<LevelRenderer>& level, GameScene& game)
    : Entity{0, MAX_POSITION}, m_level{level}, m_game{game}
{ }

void Player::update(const Engine::Input &in)
{
    if(m_moveCooldown > 0)
        m_moveCooldown -= 1;
    if(m_shootCooldown > 0)
        m_shootCooldown -= 1;
    
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

    if(m_shootCooldown <= 0 && in.isKeyPressed(Engine::KEY_R))
    {
        std::shared_ptr<Missile> missile{new Missile(
            m_line % m_level->laneCount(), *m_level.get())};
        m_game.addMissile(missile);

        m_shootCooldown = SHOOT_COOLDOWN;
    }
}

void Player::render(const Output &out) const
{
    const std::pair<Line2f, Line2f> lanes = m_level->laneLines(m_line);

    const Vect2f fromCenter{
        Vect2f::middle(lanes.first.first, lanes.second.first),
        Vect2f::middle(lanes.first.second, lanes.second.second)
    };

    const Vect2f end = Vect2f::middle(lanes.first.second, lanes.second.second);

    // TODO adapt drawing to have 90 degrees angle, and not directly attached to line
    out.setColor(Color::YELLOW);
    out.drawLine(lanes.first.second, end + fromCenter * 0.3f);
    out.drawLine(lanes.second.second, end + fromCenter * 0.3f);
}
