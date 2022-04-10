
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "entity.hpp"

#include <memory>
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
    Enemy(uint line, double speed, EnemyShape type,
        const std::shared_ptr<LevelRenderer>& level);

    EnemyShape type() const;

    /**
     * @brief tell if enemy as reach opposite line, if so then destroy it
     */
    bool asReachEnd() const; 

    /**
     * @brief update postion and line depending on speed
     */
    virtual void update(const Engine::Input &in) override;

    virtual void render(const Engine::Output &out) const override;

    static const Engine::Color ENEMY_COLOR;

private:
    double m_speed;
    EnemyShape m_type;
    
    const std::shared_ptr<LevelRenderer>& m_level;

};

#endif
