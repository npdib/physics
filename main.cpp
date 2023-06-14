/*This source code copyrighted by Lazy Foo' Productions 2004-2023
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The window we'll be rendering to
SDL_Window* window = NULL;

//The surface contained by the window
SDL_Surface* screenSurface = NULL;

SDL_Event e;

bool init(void);
void close(void);

bool init(void)
{
	bool init_success = false;

	if (SDL_Init(SDL_INIT_VIDEO) >= 0)
	{
		//Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window != NULL)
		{
			//Get window surface
			screenSurface = SDL_GetWindowSurface(window);

			init_success = true;
		}
		else
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
	}
	else
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}

	return init_success;
}

void close(void)
{
	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//Initialize SDL
	if(init())
	{
		//Fill the surface white
		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
		//Update the surface
		SDL_UpdateWindowSurface(window);

		bool quit = false;

		// main loop
		while (!quit)
		{
			// event polling
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT) 
					quit = true;
			}

			//Update the surface
			SDL_UpdateWindowSurface(window);
		}
	}

	close();

	return 0;
}
