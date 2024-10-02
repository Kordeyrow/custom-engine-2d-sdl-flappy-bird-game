#pragma once
struct Vector2 {
	float x;
	float y;
	Vector2 operator* (float mul) {
		return Vector2{ x * mul, y * mul };
	}
	Vector2 operator/ (float div) {
		if (div == 0) {
			return Vector2{ x , y };
		}
		return Vector2{ x / div, y / div };
	}
	Vector2 operator+ (Vector2 other) {
		return Vector2{ x + other.x, y * other.y };
	}
	Vector2 operator+= (Vector2 other) {
		this->x += other.x;
		this->y += other.y;
		return *this;
	}
};

