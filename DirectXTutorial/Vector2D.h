#pragma once

class Vector2D
{
public:
	Vector2D() : x(0), y(0) {}
	Vector2D(float x, float y) : x(x),  y(y) {}
	Vector2D(const Vector2D& vector) : x(vector.x),  y(vector.y) {}

	Vector2D operator *(const float num)
	{
		return Vector2D(x * num, y * num);
	}

	Vector2D operator +(const Vector2D& vec)
	{
		return Vector2D(x + vec.x, y + vec.y);
	}

	~Vector2D() {}

public:
	float x, y;
};