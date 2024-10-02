#pragma once
class Gameobject {
	int _id;
	static int next_id;

public:
	Gameobject() : _id(next_id++) { }
	int id() const { return _id; };
};

using GameobjectID = size_t;

