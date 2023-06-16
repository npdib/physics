#pragma once
#include "Object.h"
class Ball :
    public Object
{
public:
    Ball(uint16_t xPos, uint16_t yPos, uint16_t width, uint16_t height, SDL_Renderer* renderer);
};

