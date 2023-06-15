#include "Game.h"

// private:

bool Game::init_sdl()
{
	bool success = false;

	if (SDL_Init(SDL_INIT_VIDEO) >= 0)
	{
		success = true;
	}
	else
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}

	return success;
}

bool Game::init_window()
{
	bool success = false;

	//Create mWindow
	mWindow = SDL_CreateWindow("physics ...", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, kScreenWidth, kScreenHeight, SDL_WINDOW_SHOWN);
	if (mWindow != nullptr)
	{
		//Get mWindow surface
		mSurface = SDL_GetWindowSurface(mWindow);

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
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (mRenderer != nullptr)
	{
		SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		success = true;
	}
	else
	{
		printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
	}

	return success;
}

bool Game::load_background()
{
	bool success = false;

	mBackgroundImage = SDL_LoadBMP("Images/brick_wall.bmp");

	if (mBackgroundImage != nullptr)
	{
		mBackground = SDL_CreateTextureFromSurface(mRenderer, mBackgroundImage);
		success = true;
	}
	else
	{
		printf("Background could not be loaded! SDL_Error: %s\n", SDL_GetError());
	}
	return success;
}



void Game::poll_events()
{
	// event polling
	while (SDL_PollEvent(&mEvent))
	{
		if (mEvent.type == SDL_QUIT)
			mQuit = true;

		switch (mEvent.key.keysym.sym)
		{
		case SDLK_RIGHT:
			SDL_SetRenderDrawColor(mRenderer, 0xFF, 0x00, 0xFF, 0xFF);
			break;
		case SDLK_LEFT:
			SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			break;
		case SDLK_SPACE:
		{
			Object temp("images/ball.bmp", rand() % kScreenWidth, rand() % kScreenHeight, 50, 50, mRenderer);
			mObjects.push_back(temp);
			break;
		}
		default:
			break;
		}
	}
}

// public:

Game::Game() : mWindow(nullptr), mSurface(nullptr), mRenderer(nullptr), mBackgroundImage(nullptr), mBackground(nullptr), mQuit(false)
{
	mQuit = !init_sdl() || !init_window() || !init_renderer() || !load_background();
	Object temp("images/ball.bmp", 50, 50, 50, 50, mRenderer);
	mObjects.push_back(temp);
}

Game::~Game()
{
	// Deallocate surface
	SDL_FreeSurface(mBackgroundImage);
	SDL_DestroyTexture(mBackground);
	mBackgroundImage = nullptr;
	mBackground = nullptr;

	// destroy renderer
	SDL_DestroyRenderer(mRenderer);
	mRenderer = nullptr;

	// destroy surface
	SDL_FreeSurface(mSurface);
	mSurface = nullptr;

	//Destroy mWindow
	SDL_DestroyWindow(mWindow);
	mWindow = nullptr;

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
	int counter = 0;
	SDL_RenderCopy(mRenderer, mBackground, nullptr, nullptr);
	for(auto it = mObjects.begin(); it != mObjects.end(); ++it)
	{
		it->render();
		counter++;
		printf("rendered %d ball", counter);
	}

	/*for (auto image = mObjects.begin(); image < mObjects.end(); image++)
	{
		image->render();
		uint16_t x, y;
		image->getPos(x, y);
		printf("rendering object at x: %d,\ty: %d\n", x, y);
	}*/
	//Update the surface
	SDL_RenderPresent(mRenderer);
}