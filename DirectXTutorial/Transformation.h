#pragma once
#include "Component.h"

#include "Matrix4x4.h"

class Transformation : public Component
{
public:
	Transformation(SceneObject* owner);
	~Transformation();

	void scale(Vector3D deltaScale);
	void rotate(Vector3D deltaRot);
	void move(Vector3D deltaPos);

	void update() override;

	Matrix4x4 m_transformation;

	// Transformations
	Vector3D m_pos = Vector3D(0);
	Vector3D m_rot = Vector3D(0);
	Vector3D m_scale = Vector3D(1);
};