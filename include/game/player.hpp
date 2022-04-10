#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "entity.hpp"

#include <memory>

#include "levelrenderer.hpp"

class GameScene;

class Player
    : public Entity
{
public:
    Player(LevelRenderer& level, GameScene& game);

    virtual void update(const Engine::Input &in) override;
    virtual void render(const Engine::Output &out) const override;

private:
    LevelRenderer& m_level;
    GameScene& m_game;

    int m_moveCooldown, m_shootCooldown;

    /** How many updates before a player can move again */
    static const int MOVE_COOLDOWN = 5;

    /** How many updates before a player can shoot again */
    static const int SHOOT_COOLDOWN = 15;

};

#endif
