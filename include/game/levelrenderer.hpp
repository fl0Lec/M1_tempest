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
#include "enemy.hpp"

// Use a pair of vector to describe a line,
//  first vector is the point near the center
//  second vector is the point near the player
using Line2f = std::pair<Engine::Vect2f, Engine::Vect2f>;

/**
 * @brief Describes the different possible levels
 */
enum LevelType
{
    PLUS,
    SQUARE,
    TRIANGLE,
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

    /**
     * @brief Draw type enemy at a given position in line
     */
    void drawEnemy(std::shared_ptr<Enemy> e);

    /**
     * @brief Clear all enemy line
     */
    void clearEnemy();

    virtual void render(const Engine::Output &out) const override;
    virtual void update(const Engine::Input &in) override;

protected:
    /**
     * @brief Computes the structure of a level based on its type
     */
    static std::vector<Line2f> levelBasePoints(LevelType type);

    /**
     * @brief Get the two lines associated to a lane number
     * 
     * @param lane Number of the lane
     */
    std::pair<Line2f, Line2f> laneLines(size_t lane);

    /**
     * @brief Normalize a line to fit in the window
     */
    Line2f normalizeLine(Line2f line);

    /**
    * @brief move point (modify) in between himself and the center by a factor of h
    */
    void homothetie(Engine::Vect2f& A, double h, const Engine::Vect2f& center);

private:
    const LevelType m_type;
    const Engine::Vect2f m_center;
    
    size_t m_playerLane;
    size_t m_laneCount;
    
    /** Lines to be drawned as background */
    std::vector<Line2f> m_lines;

    std::vector<std::shared_ptr<std::vector<Line2f>>> m_enemy_lines;

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

Engine::Vect2f vectorized(Line2f l);

void putinU(Engine::Vect2f &p, const Engine::Vect2f& U, const Engine::Vect2f& A);


#endif
