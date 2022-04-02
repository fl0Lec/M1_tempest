/**
 * @file output.hpp
 * @brief Wrapper for everything related to game's output
 */

#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include <memory>
#include <SDL.h>

#include "color.hpp"
#include "geometry.hpp"
#include "vect2.hpp"

namespace Engine
{

/**
 * @brief Wrapper for everything related to drawing in a SDL window
 */
class Output
{

public:
    Output();
    Output(SDL_Renderer * sdl_render);

    /**
     * @brief Clear the entier drawing surface
     */
    void clear(Color color = Color::BLACK) const;

    /**
     * @brief Set the current drawing color
     */
    void setColor(Color color) const;

    /**
     * @brief Draw a point on the surface
     */
    void drawPoint(Vect2f p) const;

    /**
     * @brief Draw a line on the surface from source point to destination point
     * 
     * @param s Source point
     * @param d Destination point
     */
    void drawLine(Vect2f s, Vect2f d) const;

    void drawLine(Line2f l) const;

    /**
     * @brief Render all buffered drawing operations on screen
     */
    void render() const;

private:
    SDL_Renderer * m_render;

};

};

#endif
