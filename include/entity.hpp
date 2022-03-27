#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "gameobject.hpp"

typedef unsigned int uint;

class Entity
    : public Engine::GameObject
{
public:
    /**
     * @param line  number of line where start
     * @param position original position (default 0=center)
     */
    Entity(uint line, double position=0);

    /**
     * @brief get and set the line in which is the element
     */
    unsigned int getLine() const;
    void setLine(uint newLine);

    /**
     * @brief return the relative postion in the line
     */
    double getPosition() const;
    
private:
    uint m_line;
    double m_position;
};

#endif