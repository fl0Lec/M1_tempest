#ifndef __ENEMIE_H__
#define __ENEMIE_H__

#include "gameobject.hpp"
#include "vect2.hpp"

#include <vector>

class Enemy
    : public Engine::GameObject 
{
public :
    /**
     * @param line numeber of line where start
     * @param speed speed of the element in the line
     * @param type 
     */
    //Enemy();
    Enemy(uint line, double speed, Engine::EnemyShape type);

    uint getLine() const;
    void setLine(uint newLine);

    double getPosition() const;
    Engine::EnemyShape getType() const;

    /**
     * @brief tell if enemy as reach opposite line, if so then destroy it
     */
    bool asReachEnd() const; 

    /**
     * @brief update postion and line depending on speed
     */
    void update (const Engine::Input &in) override;
    
    void render(const Engine::Output &out) const override;


private:
    uint m_line;
    double m_position;
    double m_speed;
    Engine::EnemyShape m_type;

};
#endif