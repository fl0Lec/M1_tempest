
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "entity.hpp"

#include <vector>

#include "gameobject.hpp"
#include "vect2.hpp"

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
    //Enemy();
    Enemy(uint line, double speed, EnemyShape type);

    EnemyShape getType() const;

    /**
     * @brief tell if enemy as reach opposite line, if so then destroy it
     */
    bool asReachEnd() const; 

    /**
     * @brief update postion and line depending on speed
     */
    //void update (const Engine::Input &in) override;
    


private:
    double m_speed;
    EnemyShape m_type;

};

#endif