#pragma once
#include "Component.h"

#include "Matrix4x4.h"

class Transformation : public Component
{
public:
	Transformation(SceneObject* owner);
	~Transformation();

	void update() override;
	void updateFisrtPersonRotations();

	void move(Vector3D deltaPos);
	void scale(Vector3D deltaScale);
	void rotate(Vector3D deltaRot);

	void setPosition(Vector3D position);
	void setScale(Vector3D scale);
	void setRotation(Vector3D rotation);

	const Vector3D getPosition();
	const Vector3D getScale();
	const Vector3D getRotation();
	const Matrix4x4 getWorldMatrix();

private:
	Matrix4x4 m_WorldMatrix;
	Vector3D m_pos = Vector3D(0);
	Vector3D m_rot = Vector3D(0);
	Vector3D m_scale = Vector3D(1);
};