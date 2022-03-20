
#include "game.hpp"

#include <chrono>
#include <cstdlib>
#include <iostream>

using namespace Engine;

Game::Game(const std::shared_ptr<Scene>& startScene, const std::string& name,
        size_t windowWidth, size_t windowHeight)
    : m_currentScene(startScene), m_timeBase(std::chrono::steady_clock::now())
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "Error: cannot initialize SDL" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // If window is used anywhere else than create separate class to manage it
    SDL_Window* window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight,
        SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!renderer)
    {
        std::cerr << "Error: cannot SDL renderer" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    m_output = Output(renderer);
}

double Game::currentTimeMillis() const
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - m_timeBase
    ).count();
}

void Game::run()
{
    const double updatePeriod = 1.0 / Game::UPDATES_PER_SECOND;
    double lastUpdate = 0;

    int fpsCount = 0;
    int updateCount = 0;

    bool quit = false;
    while(!quit)
    {
        SDL_Event event;
		while (!quit && SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			}
        }

        const double currentTime = currentTimeMillis();
        if(currentTime - lastUpdate >= updatePeriod)
        {
            update();
            lastUpdate = currentTime;

            updateCount += 1;
            if(updateCount >= Game::UPDATES_PER_SECOND)
            {
                m_lastSecondFpsCount = fpsCount;
                fpsCount = 0;
                updateCount = 0;
            }
        }
        else
            render();
    }

    SDL_Quit();
}

const std::shared_ptr<Scene>& Game::currentScene() const
{
    return m_currentScene;
}

void Game::setCurrentScene(const std::shared_ptr<Scene>& scene)
{
    m_currentScene = scene;
}

unsigned int Game::FPSLimit() const
{
    // TODO
}

void Game::setFPSLimit(unsigned int limit)
{
    // TODO
}

unsigned int Game::lastSecondFPSCount() const
{
    return m_lastSecondFpsCount;
}

void Game::update()
{
    m_input.update();
    m_currentScene->update(m_input);
}

void Game::render()
{
    m_output.clear();

    m_currentScene->render(m_output);

    m_output.render();
}
