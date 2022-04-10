/**
 * @file color.hpp
 * @brief Representation of a color for drawings
 */

#ifndef __COLOR_H__
#define __COLOR_H__

#include <SDL.h>

namespace Engine
{

struct Color
{
    /** Basic colors */
    const static Color RED;
    const static Color GREEN;
    const static Color BLUE;
    const static Color YELLOW;
    const static Color MAGENTA;
    const static Color BLACK;
    const static Color WHITE;

    Uint8 r;    /**< Red component */
    Uint8 g;    /**< Green component */
    Uint8 b;    /**< Blue component */

    Uint8 a;    /**< Opacity */

    Color(Uint8 r1, Uint8 g1, Uint8 b1, Uint8 a1 = 255);

    Color(const Color & color);
    Color operator=(const Color & color) const;
};

bool operator==(const Color & c1, const Color & c2);
bool operator!=(const Color & c1, const Color & c2);

};

#endif
