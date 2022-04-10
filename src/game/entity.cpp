
#include "entity.hpp"

#include "color.hpp"

Entity::Entity(uint line, double position)
    : m_line(line), m_position(position) {} 

uint Entity::line() const 
{
    return m_line;
}

void Entity::setLine(uint newLine)
{
    m_line = newLine;
}


double Entity::position() const
{
    return m_position;
}
