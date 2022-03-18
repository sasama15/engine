#include "SampleGame.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    Framework* game = new SampleGame();

    game->Run();

    delete game;

	return 0;
}