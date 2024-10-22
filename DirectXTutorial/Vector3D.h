#pragma once

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

	Vector3D operator *(const float num)
	{
		return Vector3D(x * num, y * num, z * num);
	}


	Vector3D operator +(const Vector3D& vec)
	{
		return Vector3D(x + vec.x, y + vec.y, z + vec.z);
	}

	static Vector3D RIGHT() { return Vector3D(1, 0, 0); }
	static Vector3D UP() { return Vector3D(0, 1, 0); }
	static Vector3D FORWARD() { return Vector3D(0, 0, 1); }

	float x, y, z;
};