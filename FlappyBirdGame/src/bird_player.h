#pragma once
#include "structs.h"
#include "Physics/Rigidbody.h"
#include "texture_manager.h"
#include "IUpdate.h"
#include "InputContainer.h"
#include "Physics/PhysicsSystem.h"

class BirdPlayer : public IUpdate, Gameobject
{
	// Dependencies
	TextureManager* texture_manager;

	// Components
	Rigidbody rigidbody;

public:
	BirdPlayer(TextureManager* texture_manager, Vector2 initialPos);
	void update(double elapsedTime);
	void movement_update(double elapsedTime);

	Rigidbody* get_rigidbody() { return &rigidbody; }

	Sprite* sprite;
};

