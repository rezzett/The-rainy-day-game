#include <ctime>
#include <cstdlib>

#include "Game.h"
#include "AssetManager.h"

int main()
{
	srand(time(NULL));
	AssetManager assetManager;
	assetManager.addTexture("assets/bucket.png");
	assetManager.addTexture("assets/drop.png");
	assetManager.addTexture("assets/rainbg.png");

	Game game(std::move(assetManager));
	game.run();
	return 0;
}