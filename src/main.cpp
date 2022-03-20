
#include <memory>

#include "game.hpp"
#include "bnojourscene.hpp"

using namespace Engine;

#define WINDOW_WIDTH  720
#define WINDOW_HEIGHT 480

// TODO Remove all
int main()
{
	std::shared_ptr<BnojourScene> startScene(new BnojourScene());
	std::shared_ptr<Game> game(new Game(startScene, "Tempest",
		WINDOW_WIDTH, WINDOW_HEIGHT));

	game->run();

	return 0;
}
