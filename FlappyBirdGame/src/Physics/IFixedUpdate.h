#pragma once
#include "Transform.h"

class IFixedUpdate {
public:
	virtual Transform* get_transform() = 0;
	Vector2 currentForce;
};

