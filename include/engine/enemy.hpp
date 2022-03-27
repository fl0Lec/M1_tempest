#ifndef __ENEMIE_H__
#define __ENEMIE_H__

#include "entity.hpp"
#include "gameobject.hpp"
#include "vect2.hpp"

#include <vector>

class Enemy
    : public Entity
{
public :
    /**
     * @param line numeber of line where start
     * @param speed speed of the element in the line
     * @param type 
     */
    //Enemy();
    Enemy(uint line, double speed, Engine::EnemyShape type);

    Engine::EnemyShape getType() const;

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
    Engine::EnemyShape m_type;

};
#endif