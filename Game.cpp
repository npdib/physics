#include "Game.h"

// private:

bool Game::init_window()
{
	bool success = false;

	//Create window
	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, kScreenWidth, kScreenHeight, SDL_WINDOW_SHOWN);
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

bool Game::init_renderer()
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


void Game::poll_events()
{
	// event polling
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			mQuit = true;

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
}


// public:

Game::Game() : window(nullptr), screenSurface(nullptr), g_renderer(nullptr), mQuit(false)
{
	if (SDL_Init(SDL_INIT_VIDEO) >= 0)
	{
		mQuit = !init_window() || !init_renderer();
	}
	else
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		mQuit = true;
	}
}

Game::~Game()
{
	printf("running destructor...\n");
	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();
}

bool Game::running()
{
	return !mQuit;
}


void Game::run()
{
	poll_events();
}


void Game::render()
{
	SDL_RenderFillRect(g_renderer, NULL);
	//Update the surface
	SDL_RenderPresent(g_renderer);
}
