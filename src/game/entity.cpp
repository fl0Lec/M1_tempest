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

void Entity::update(const Engine::Input &in)
{
    // TODO Implement here or in sub-classes
}

void Entity::render(const Engine::Output &out) const
{
    // TODO Implement here or in sub-classes
}
