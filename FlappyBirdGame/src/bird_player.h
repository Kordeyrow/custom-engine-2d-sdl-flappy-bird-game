#pragma once
#include "structs.h"
#include "Physics/IFixedUpdate.h"
#include "texture_manager.h"
#include "IUpdate.h"
#include "InputContainer.h"

class BirdPlayer : public IUpdate, IFixedUpdate
{
	// ref
	TextureManager* texture_manager;

public:
	BirdPlayer(TextureManager* texture_manager, Vector2 initialPos);
	void update(double elapsedTime);
	void movement_update(double elapsedTime);

	Sprite* sprite;

	// Inherited via IFixedUpdate
	Transform* get_transform() override;
};

