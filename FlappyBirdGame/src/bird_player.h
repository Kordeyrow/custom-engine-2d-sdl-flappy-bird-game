#pragma once
#include "structs.h"
#include "texture_manager.h"
#include "IUpdate.h"

class BirdPlayer : public IUpdate
{
	// ref
	TextureManager* texture_manager;

public:
	Vector2 position;
	Sprite* sprite;
	BirdPlayer(TextureManager* texture_manager, Vector2 initialPos);
	void update(float deltatime);
};

