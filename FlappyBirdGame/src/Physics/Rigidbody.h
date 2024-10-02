#pragma once
#include "Transform.h"

class Rigidbody {
	friend class PhysicsSystem;
	Vector2 final_force;
public:
	virtual Transform* get_transform() = 0;
};

