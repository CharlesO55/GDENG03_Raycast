#pragma once
#include "Primitive.h"
class Circle : public Primitive
{
public:
	Circle();
	~Circle();

	virtual void update() override;

private:
	Vector3D moveDir;
	float radius = 0.1f;
};