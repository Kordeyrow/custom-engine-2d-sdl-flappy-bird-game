#pragma once
#include "structs.h"
#include "Physics/Rigidbody.h"
#include "texture_manager.h"
#include "IUpdate.h"
#include "InputContainer.h"
#include "Physics/PhysicsSystem.h"

class BirdPlayer : public IUpdate, Rigidbody
{
	// ref
	TextureManager* texture_manager;

public:
	BirdPlayer(TextureManager* texture_manager, Vector2 initialPos);
	void update(double elapsedTime);
	void movement_update(double elapsedTime);

	Sprite* sprite;

	// Inherited via Rigidbody
	Transform* get_transform() override;
};

