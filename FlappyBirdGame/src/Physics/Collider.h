#pragma once
#include "../engine/Gameobject.h"

class Collider {
	Vector2 size;
	Gameobject* gameobject;

	Collider(Vector2 _size, Gameobject* _gameobject) 
		: size(_size), gameobject(_gameobject) {}
};

