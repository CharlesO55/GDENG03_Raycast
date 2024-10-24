#include "RaycastComponent.h"

#include "Debugger.h"
#include <iostream>
#include "SceneObject.h"


RaycastComponent::RaycastComponent(SceneObject* owner) : Component(ComponentID::RAYCAST, owner)
{
}

void RaycastComponent::update()
{
	if(m_IsTriggered)
		Debugger::Warning("Hit");
}

void RaycastComponent::onHit(const Vector3D& hitDir)
{
	//m_IsTriggered = true;
	Debugger::Success("Hit");
}
