#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "entity.hpp"
#include "levelrenderer.hpp"

#include <memory>

class Player
    : public Entity
{
public:
    Player(const std::shared_ptr<LevelRenderer>& level);

    virtual void update(const Engine::Input &in) override;
    virtual void render(const Engine::Output &out) const override;

private:
    std::shared_ptr<LevelRenderer> m_level;

    int m_moveCooldown;

    /** How many updates between player's moves */
    static const int MOVE_COOLDOWN = 5;

};

#endif