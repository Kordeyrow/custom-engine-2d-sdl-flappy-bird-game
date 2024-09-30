#pragma once
#include "structs.h"
#include "texture_manager.h"
#include "IUpdate.h"
#include "InputManager.h"

class BirdPlayer : public IUpdate
{
	// ref
	TextureManager* texture_manager;

public:
	BirdPlayer(TextureManager* texture_manager, Vector2 initialPos);
	void update(float deltatime);
	void movement_update(float deltatime);

	Vector2 position{};
	Sprite* sprite;
};

