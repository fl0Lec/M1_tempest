#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "gameobject.hpp"

#include "color.hpp"

typedef unsigned int uint;

class Entity
    : public Engine::GameObject
{
public:
    /**
     * @param line  number of line where start
     * @param position original position on the line, between the center=0 
        and the player=100
     */
    Entity(uint line, double position = 0.0f);

    /**
     * @brief get and set the line in which is the element
     */
    unsigned int line() const;
    void setLine(uint line);

    /**
     * @brief return the relative postion in the line
     */
    double position() const;

    static constexpr float MAX_POSITION = 100.0f;
    
protected:
    uint m_line;
    double m_position;

};

#endif