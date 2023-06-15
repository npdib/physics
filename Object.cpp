#include "Object.h"

Object::Object(char const * path, uint16_t xPos, uint16_t yPos, uint16_t width, uint16_t height, SDL_Renderer* renderer) : mXpos(xPos), mYpos(yPos), mWidth(width), mHeight(height), mImage(nullptr), mRenderer(renderer)
{
	SDL_Surface* imageSurface = SDL_LoadBMP(path);
	mImage = SDL_CreateTextureFromSurface(mRenderer, imageSurface);
	SDL_FreeSurface(imageSurface);
}

Object::~Object()
{
	SDL_DestroyTexture(mImage);
	mImage = nullptr;
}

void Object::render(void)
{
	const SDL_Rect renderQuad = { mXpos, mYpos, mWidth, mHeight };
	SDL_RenderCopy(mRenderer, mImage, nullptr, &renderQuad);
}
