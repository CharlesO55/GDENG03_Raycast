#pragma once
#include "Component.h"

#include "Vector3D.h"


class RaycastComponent : public Component
{
public:
	RaycastComponent(SceneObject* owner);
	

	void update() override;
	void onHit(const Vector3D& hitDir);

	bool m_IsTriggered = false;
};