/*This source code copyrighted by Lazy Foo' Productions 2004-2023
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include "Game.h"


int main(int argc, char* args[])
{
	Game game;

	while (game.running())
	{
		game.run();
		game.render();
	}

	return 0;
}
