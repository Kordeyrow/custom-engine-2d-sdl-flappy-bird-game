#pragma once
#include "structs.h"
#include "texture_manager.h"

class BirdPlayer 
{
	// ref
	TextureManager* texture_manager;

public:
	Sprite* sprite;
	BirdPlayer(TextureManager* texture_manager, Vector2 initialPos);
	void Update();
};

