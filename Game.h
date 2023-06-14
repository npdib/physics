#pragma once
#include <stdio.h>
#include <SDL.h>

class Game
{
private:
	//Screen dimension constants
	static constexpr int kScreenWidth = 640;
	static constexpr int kScreenHeight = 480;

	//The window we'll be rendering to
	SDL_Window* window;

	//The surface contained by the window
	SDL_Surface* screenSurface;

	// Renderer
	SDL_Renderer* g_renderer;

	// Event for the event handler
	SDL_Event e;
	bool mQuit;

	bool init_window(void);
	bool init_renderer(void);

	void poll_events(void);

public:
	Game(void);
	~Game();
	bool running(void);
	void run(void);
	void render(void);
};

