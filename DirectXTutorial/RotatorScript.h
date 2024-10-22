#pragma once
#include "Component.h"

#include "Vector3D.h"

class RotatorScript : public Component
{
public:
	RotatorScript(SceneObject* owner);

	void update() override;


private:
	Vector3D m_rotSpeed;
};