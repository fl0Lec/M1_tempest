/**
 * @file levelrenderer.hpp
 * @brief Draw game levels (background)
 */

#ifndef __LEVELRENDERER_H__
#define __LEVELRENDERER_H__

#include "gameobject.hpp"

#include <sys/types.h>
#include <utility>
#include <vector>

#include "color.hpp"
#include "output.hpp"
#include "vect2.hpp"

/**
 * @brief Describes the different possible levels
 */
enum LevelType
{
    SQUARE /** Simple square, might get removed because isn't a real level */
};

/**
 * @brief Render the background of a level
 * 
 */
class LevelRenderer
    : public Engine::GameObject
{
public:
    /**
     * @param center Center of the level
     * @param type Type of level
     */
    LevelRenderer(const Engine::Vect2f& center, LevelType type);

    /**
     * @brief Counts the number of lanes in the selected level
     */
    size_t laneCount() const;

    /**
     * @brief Set the lane in which the player is located
     */
    void setPlayerLane(size_t lane);

    virtual void render(const Engine::Output &out) const override;
    virtual void update(const Engine::Input &in) override;

protected:
    /**
     * @brief Computes the structure of a level based on its type
     */
    static std::vector<std::pair<Engine::Vect2f, Engine::Vect2f>>
        levelBasePoints(LevelType type);

    /**
     * @brief Normalize a line to fit in the window
     */
    std::pair<Engine::Vect2f, Engine::Vect2f> normalizeLine(
        std::pair<Engine::Vect2f, Engine::Vect2f> line);

private:
    const LevelType m_type;
    const Engine::Vect2f m_center;
    
    size_t m_playerLane;
    
    /** Lines to be drawned as background */
    std::vector<std::pair<Engine::Vect2f, Engine::Vect2f>> m_lines;

    static const Engine::Color DEFAULT_COLOR;
    static const Engine::Color PLAYER_COLOR;

    /**
     * @brief Pourcentage of the window occupied by the void the center
     */
    static constexpr float CENTER_SIZE = 0.05f;
    /**
     * @brief Pourcentage of the window occupied by the lanes
     */
    static constexpr float LANE_SIZE = 0.8f;

};

#endif