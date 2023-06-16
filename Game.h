#pragma once
#include <list>
#include <SDL.h>
#include "Ball.h"

class Game
{
private:
	//Screen dimension constants
	static constexpr int kScreenWidth = 640;
	static constexpr int kScreenHeight = 480;

	//The mWindow we'll be rendering to
	SDL_Window* mWindow;

	//The surface contained by the mWindow
	SDL_Surface* mSurface;

	// Renderer
	SDL_Renderer* mRenderer;

	// Event for the event handler
	SDL_Event mEvent;

	// background
	SDL_Surface* mBackgroundImage;
	SDL_Texture* mBackground;

	std::list<Object*> mObjects;

	bool mQuit;

	bool init_sdl(void);
	bool init_window(void);
	bool init_renderer(void);
	bool load_background(void);
	void poll_events(void);

public:
	Game(void);
	~Game();
	bool running(void);
	void run(void);
	void render(void);
};

