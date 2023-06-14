/*This source code copyrighted by Lazy Foo' Productions 2004-2023
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The window we'll be rendering to
SDL_Window* window = NULL;

//The surface contained by the window
SDL_Surface* screenSurface = NULL;

// Renderer
SDL_Renderer* g_renderer = NULL;

// Event for the event handler
SDL_Event e;

bool init_window(void);
bool init_renderer(void);
bool init(void);
void close(void);

bool init_window(void)
{
	bool success = false;

	//Create window
	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window != NULL)
	{
		//Get window surface
		screenSurface = SDL_GetWindowSurface(window);

		success = true;
	}
	else
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
	}

	return success;
}

bool init_renderer()
{
	bool success = false;

	//Create renderer
	g_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (g_renderer != NULL)
	{
		SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		success = true;
	}
	else
	{
		printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
	}

	return success;
}


bool init(void)
{
	bool success = false;

	if (SDL_Init(SDL_INIT_VIDEO) >= 0)
	{
		success = !(!init_window() || !init_renderer());
	}
	else
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}

	return success;
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
		SDL_RenderFillRect(g_renderer, NULL);
		//Update the surface
		SDL_RenderPresent(g_renderer);

		bool quit = false;

		// main loop
		while (!quit)
		{
			// event polling
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT) 
					quit = true;

				switch (e.key.keysym.sym)
				{
				case SDLK_RIGHT:
					SDL_SetRenderDrawColor(g_renderer, 0xFF, 0x00, 0xFF, 0xFF);
					break;
				case SDLK_LEFT:
					SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
					break;
				default:
					break;
				}

			}

			SDL_RenderFillRect(g_renderer, NULL);
			//Update the surface
			SDL_RenderPresent(g_renderer);
		}
	}

	close();

	return 0;
}
