
#include <iostream>
#include <memory>

#include "game.hpp"
#include "scene.hpp"
#include "vect2.hpp"

#include "gamescene.hpp"
#include "bnojourscene.hpp"
#include "leveldisplayscene.hpp"

using namespace Engine;

#define WINDOW_WIDTH  720
#define WINDOW_HEIGHT 480

// TODO Remove all
int main()
{
	std::shared_ptr<Game> game(new Game("Tempest", WINDOW_WIDTH, WINDOW_HEIGHT));	
	Game::setInstance(game);

	// Debug scene
	// std::shared_ptr<LevelDisplayScene> displayScene{new LevelDisplayScene{}};
	// game->setCurrentScene(displayScene);

	std::shared_ptr<GameScene> gameScene{new GameScene{}};
	game->setCurrentScene(gameScene);

	game->run();

	return 0;
}
