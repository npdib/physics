#pragma once
#include <cstdint>
#include <SDL.h>

class Object
{
private:
	// basic properties
	uint16_t mXpos;
	uint16_t mYpos;
	uint16_t mWidth;
	uint16_t mHeight;

	SDL_Texture* mImage;

	// pointer to existing renderer
	SDL_Renderer* mRenderer;

public:
	Object(char const * path, uint16_t xPos, uint16_t yPos, uint16_t width, uint16_t height, SDL_Renderer* renderer);
	~Object();

	void render(void);

};

