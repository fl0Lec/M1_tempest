#include "entity.hpp"



Entity::Entity(uint line, double postion):m_line(line), m_position(postion) {} 


uint Entity::getLine() const 
{
    return m_line;
}

void Entity::setLine(uint newLine)
{
    m_line = newLine;
}


double Entity::getPosition() const
{
    return m_position;
}