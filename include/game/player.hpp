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

private:
    std::shared_ptr<LevelRenderer> m_level;

    int m_moveCooldown;
    size_t m_currentLane;

    /** How many updates between player's moves */
    static const int MOVE_COOLDOWN = 5;

};

#endif