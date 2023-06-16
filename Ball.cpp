#include "Ball.h"

Ball::Ball(uint16_t xPos, uint16_t yPos, uint16_t width, uint16_t height, SDL_Renderer* renderer) : Object("images/ball.bmp", xPos, yPos, width, height, renderer)
{
	
	SDL_Surface* imageSurface = SDL_LoadBMP("images/ball.bmp");
	SDL_SetColorKey(imageSurface, SDL_TRUE, SDL_MapRGB(imageSurface->format, 0xff, 0xff, 0xff));
	mImage = SDL_CreateTextureFromSurface(mRenderer, imageSurface);
	SDL_FreeSurface(imageSurface);
}
