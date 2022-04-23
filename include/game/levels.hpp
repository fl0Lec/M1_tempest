/**
 * @file levels.hpp
 * @brief Ressources to build the different levels
 */

#ifndef __LEVELS_H__
#define __LEVELS_H__

#include "geometry.hpp"
#include "vect2.hpp"

#include <vector>
#include <utility>

/**
 * @brief Describes the different possible levels
 */
enum LevelType
{
    PLUS,
    SQUARE,
    TRIANGLE,
    CIRCLE,
    FLAT,
    STAR,
};

/**
 * Base for the different levels
 */
class Level
{
public:
    static const std::vector<Engine::Line2f> basePlus;
    static const std::vector<Engine::Line2f> baseSquare;
    static const std::vector<Engine::Vect2f> baseTriangle;
    static const std::vector<Engine::Vect2f> baseCircle;
    static const std::vector<float> baseFlat;
    static const std::vector<Engine::Vect2f> baseStar;

    /**
     * @brief Get the structure of a level based on its type
     */
    static std::vector<Engine::Line2f> levelBasePoints(LevelType type);
};


#endif
