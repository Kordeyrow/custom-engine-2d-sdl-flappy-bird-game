#pragma once
#include "Transform.h"
#include "Collider.h"
#include "../engine/gameobject.h"

class Rigidbody : Component {

	friend class PhysicsSystem;
	Vector2 final_force;

	// dependency

public:
	const Gameobject* gameobject;
	const Transform* transform;
	Collider* collider; 

	Rigidbody(Gameobject* gameobject)
		: gameobject(gameobject){
		transform = &gameobject->transform;

		/*collider = gameobject->get_component<Collider>();
		if (collider == nullptr) {
			collider = gameobject->add_component<Collider>();
		}*/
	}
};

