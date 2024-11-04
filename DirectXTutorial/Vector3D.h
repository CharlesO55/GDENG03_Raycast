#pragma once
#include <iostream>

class Vector3D {
public:
	Vector3D() : x(0), y(0), z(0) {};
	Vector3D(float identicalValue) : x(identicalValue), y(identicalValue), z(identicalValue) {};
	Vector3D(float x, float y) : x(x), y(y), z(0) {};
	Vector3D(float x, float y, float z) : x(x), y(y), z(z) {};
	Vector3D(const Vector3D& vector) : x(vector.x), y(vector.y), z(vector.z) {};

	static Vector3D lerp(const Vector3D& start, const Vector3D& end, const float delta)
	{
		Vector3D v;
		v.x = start.x * (1.0f - delta) + end.x * (delta);
		v.y = start.y * (1.0f - delta) + end.y * (delta);
		v.z = start.z * (1.0f - delta) + end.z * (delta);
		return v;
	}

	static float dot(const Vector3D& a, const Vector3D& b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	static Vector3D inverse(const Vector3D& vec) {
		return Vector3D(1 / vec.x, 1 / vec.y, 1 / vec.z);
	}

	Vector3D operator *(const float num) const { return Vector3D(x * num, y * num, z * num); }
	Vector3D operator /(const float num) const { return Vector3D(x / num, y / num, z / num); }

	Vector3D operator +(const Vector3D& vec) const { return Vector3D(x + vec.x, y + vec.y, z + vec.z); }
	Vector3D operator -(const Vector3D& vec) const { return Vector3D(x - vec.x, y - vec.y, z - vec.z); }

	float magnitude() const 
	{
		return std::sqrt(x * x + y * y + z * z);
	}

	void normalize() 
	{
		float len = magnitude();
		if (len > 0.00001f) {
			x /= len;
			y /= len;
			z /= len;
		}
	}

	static float distance(const Vector3D& a, const Vector3D& b) {
		float x = a.x - b.x;
		float y = a.y - b.y;
		float z = a.z - b.z;

		return sqrt(x*x + y*y + z*z);
	}

	static float maxComponent(const Vector3D& vec) {
		float output = vec.x;
		if (vec.y > output)	output = vec.y;
		if (vec.z > output)	output = vec.z;
		return output;
	}

	static float minComponent(const Vector3D& vec) {
		float output = vec.x;
		if (vec.y < output)	output = vec.y;
		if (vec.z < output)	output = vec.z;
		return output;
	}

	static Vector3D RIGHT() { return Vector3D(1, 0, 0); }
	static Vector3D UP() { return Vector3D(0, 1, 0); }
	static Vector3D FORWARD() { return Vector3D(0, 0, 1); }

	float x, y, z;
};