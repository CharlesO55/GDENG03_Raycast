#pragma once
#include "Component.h"

#include "Matrix4x4.h"

class Transformation : public Component
{
public:
	Transformation(SceneObject* owner);
	~Transformation();

	void update() override;

	void move(const Vector3D deltaPos);
	void scale(const Vector3D deltaScale);
	void rotate(const Vector3D deltaRot);

	void setPosition(const Vector3D position);
	void setScale(const Vector3D scale);
	void setRotation(const Vector3D rotation);
	void setWorldMatrix(const Matrix4x4 matrix);

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