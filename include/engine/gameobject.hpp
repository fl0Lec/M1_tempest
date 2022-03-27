/**
 * @file gameobject.hpp
 * @brief Object handle by the game engine
 */

#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "input.hpp"
#include "output.hpp"

enum EnemyShape {SQUARE_MIDDLE};

namespace Engine
{

/**
 * @brief Abstract class to represent an object in the game
 */
class GameObject
{
public:
    
    /**
     * @brief Update the current object. This function will be called
     *  periodically by the game engine
     * 
     * @param in Input state
     */
    virtual void update(const Input & in) = 0;

    /**
     * @brief Draw current object inside the appropriate context
     * 
     * @param out Output to send drawing commands
     */
    virtual void render(const Output & out) const = 0;

};

};

#endif
