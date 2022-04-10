
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "entity.hpp"

#include <vector>

#include "output.hpp"
#include "vect2.hpp"

class LevelRenderer;

enum EnemyShape {SQUARE_MIDDLE};

class Enemy
    : public Entity
{
public :
    /**
     * @param line number of line where start
     * @param speed speed of the element in the line
     * @param type 
     */
    Enemy(uint line, double speed, EnemyShape type, const LevelRenderer& level);

    EnemyShape type() const;

    /**
     * @brief tell if enemy as reach opposite line, if so then destroy it
     */
    bool asReachEnd() const; 

    /**
     * @brief tell how much score the player wins when killing this enemy
     */
    virtual unsigned int givenScore() const;

    /**
     * @brief update postion and line depending on speed
     */
    virtual void update(const Engine::Input &in) override;

    virtual void render(const Engine::Output &out) const override;

    static const Engine::Color ENEMY_COLOR;
    static constexpr unsigned int GIVEN_SCORE = 10;

private:
    double m_speed;
    EnemyShape m_type;
    
    const LevelRenderer& m_level;

};

#endif
