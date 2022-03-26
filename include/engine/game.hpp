/**
 * @file game.hpp
 * @brief Core of the game engine which runs the game loop and abstraction of
 *  SDL Events and Window
 */

#ifndef __GAME_H__
#define __GAME_H__

#include "singleton.hpp"

#include <chrono>
#include <memory>

#include "input.hpp"
#include "output.hpp"
#include "scene.hpp"
#include "vect2.hpp"

namespace Engine
{

class Game
    : public Singleton<Game>
{
public:
    static const int UPDATES_PER_SECOND = 20;

    /**
     * @brief Construct a new game engine, which will start by running
     *  startScene, after a call to its method run
     * 
     * @param name Name of the game, to be displayed as window title
     * @param windowWidth Window's width in pixels
     * @param windowHeight Window's height in pixels
     */
    Game(const std::string& name, size_t windowWidth, size_t windowHeight);

    /**
     * @brief Run the game engine in the current thread
     */
    void run();

    /**
     * @brief Get the current scene rendered by the game
     */
    const std::shared_ptr<Scene>& currentScene() const;

    /**
     * @brief Set the current scene
     */
    void setCurrentScene(const std::shared_ptr<Scene>& scene);

    /**
     * @brief Get the current limit of Frame Per Second
     */
    unsigned int FPSLimit() const;

    /**
     * @brief Set the current maximum count of FPS that can be rendered each
     *  second
     *  Set the limit to 0 means unlimited Frame Per Second
     */
    void setFPSLimit(unsigned int limit);

    /**
     * @brief Get the count of Frames rendered last second
     */
    unsigned int lastSecondFPSCount() const;

    /**
     * @brief Get the width of the game window
     */
    size_t width() const;

    /**
     * @brief Get the height of the game window
     */
    size_t height() const;

    /**
     * @brief Get the center of the game window
     */
    Vect2f center() const;

protected:
    void update(); // Update Input and update scene
    void render(); // Clean display and render scene

    // Helper for time management (number of milliseconds since start)
    double currentTimeMillis() const;

private:
    std::shared_ptr<Scene> m_currentScene;
    Output m_output;
    Input m_input;

    const size_t m_width;
    const size_t m_height;

    const std::chrono::time_point<std::chrono::steady_clock> m_timeBase;

    unsigned int m_fpsLimit;
    unsigned int m_lastSecondFpsCount;
};

};

#endif
