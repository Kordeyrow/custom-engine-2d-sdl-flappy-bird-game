#pragma once
#include <SDL.h>

struct Vector2 {
	float x;
	float y;
};

struct Sprite {
	SDL_Rect rect;
	SDL_Texture* texture;
	SDL_RendererFlip flip;
	double rotation;
};