/**
 * @file hershey.hpp
 * @brief Draw letters using Hershey Vector Font
 */

#ifndef __HERSHEY_H__
#define __HERSHEY_H__

#include "output.hpp"
#include "vect2.hpp"

namespace Engine
{
namespace Hershey
{

/**
 * @brief Draw given character at position using Hershey vector font
 * 
 * @param c Character to be drawn (valid characters are ASCII from 32 to 126)
 * @param pos Position to start drawing (from bottom left corner)
 * @return Vect2f Position where the letter stopped (bottom right corner)
 */
Vect2f drawLetter(const Output & out, char c, const Vect2f & pos);

/**
 * @brief Get the width a character would require to be drawn
 * 
 * @param c Character to be drawn
 * @return int Width of the character
 */
int getLetterWidth(char c);

};
};

#endif
