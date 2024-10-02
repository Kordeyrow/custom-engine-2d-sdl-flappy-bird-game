#pragma once
#include <SDL.h>
#include "Physics/Transform.h"

struct Sprite {
	Transform transform;
	SDL_Texture* texture;
	SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE;
	double rotation = 0;
};