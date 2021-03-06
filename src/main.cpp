
#include <iostream>
#include <memory>

#include "game.hpp"
#include "scene.hpp"
#include "vect2.hpp"

#include "gamescene.hpp"
#include "bnojourscene.hpp"
#include "chooselevelscene.hpp"
#include "leveldisplayscene.hpp"

using namespace Engine;

#define WINDOW_WIDTH  1080
#define WINDOW_HEIGHT 720

int main()
{
    std::shared_ptr<Game> game(new Game("Tempest", WINDOW_WIDTH, WINDOW_HEIGHT));	
    Game::setInstance(game);

    // Debug scene
    // std::shared_ptr<LevelDisplayScene> displayScene{new LevelDisplayScene{}};
    // game->setCurrentScene(displayScene);

    std::shared_ptr<ChooseLevelScene> levelsScene{new ChooseLevelScene{0}};
    game->setCurrentScene(levelsScene);

    game->run();

    return 0;
}
