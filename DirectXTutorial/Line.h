#pragma once
#include "Primitive.h"
class Line : public Primitive
{
public:
	Line(const Vector3D startPos, const Vector3D endPos);

	void draw() override;
};

