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
#include "enemy.hpp"
#include "geometry.hpp"
#include "levels.hpp"
#include "output.hpp"
#include "vect2.hpp"

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
     * @param size Size of the square that the drawing can occupy
     * @param type Type of level
     */
    LevelRenderer(const Engine::Vect2f& center, size_t size, LevelType type);

    /**
     * @brief Counts the number of lanes in the selected level
     */
    size_t laneCount() const;

    /**
     * @brief Set the lane in which the player is located
     */
    void setPlayerLane(size_t lane);

    /**
     * @brief Get the two lines associated to a lane number
     * 
     * @param lane Number of the lane
     */
    std::pair<Engine::Line2f, Engine::Line2f> laneLines(size_t lane) const;

    virtual void render(const Engine::Output &out) const override;
    virtual void update(const Engine::Input &in) override;

protected:
    /**
     * @brief Normalize a line to fit in the window
     */
    Engine::Line2f normalizeLine(Engine::Line2f line) const;

private:
    const LevelType m_type;
    const Engine::Vect2f m_center;
    const size_t m_size;
    
    size_t m_laneCount;
    
    /** Lines to be drawned as background */
    std::vector<Engine::Line2f> m_lines;
    std::vector<Engine::Line2f> m_endLines;
    std::vector<Engine::Line2f> m_selectedLines;

    static const Engine::Color DEFAULT_COLOR;
    static const Engine::Color PLAYER_COLOR;

    /**
     * @brief Pourcentage of the window occupied by the void the center
     */
    static constexpr float CENTER_SIZE = 0.05f;
    /**
     * @brief Pourcentage of the window occupied by the lanes
     */
    static constexpr float LANE_SIZE = 0.7f;

};

#endif
