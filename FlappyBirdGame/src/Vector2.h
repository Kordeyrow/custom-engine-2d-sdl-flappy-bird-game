#pragma once
struct Vector2 {
	float x = 0;
	float y = 0;

	Vector2() : x(0), y(0) {}

	Vector2(float x, float y) : x(x), y(y) {}

	static const Vector2 zero;

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

