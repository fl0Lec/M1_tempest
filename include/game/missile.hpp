#ifndef __MISSILE_H__
#define __MISSILE_H__

#include "entity.hpp"

#include "levelrenderer.hpp"

class Missile
    : public Entity
{
public:
    Missile(uint line, const LevelRenderer& level);

    virtual void update(const Engine::Input &in) override;
    virtual void render(const Engine::Output &out) const override;

    static constexpr float WIDTH = 8.0f;

    static const Engine::Color MISSILE_COLOR;

private:
    const LevelRenderer& m_level;

    static constexpr float SPEED = 1.5f;

};

#endif
