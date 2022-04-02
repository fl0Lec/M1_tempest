/**
 * @file geometry.hpp
 * @brief Geometry utilities
 */

#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include "vect2.hpp"

#include <utility>

namespace Engine
{

// Use a pair of vector to describe a line,
//  first vector is the point near the center
//  second vector is the point near the player
using Line2f = std::pair<Vect2f, Vect2f>;

};

#endif
