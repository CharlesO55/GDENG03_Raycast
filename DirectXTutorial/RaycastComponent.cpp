#include "RaycastComponent.h"

#include "Debugger.h"
#include "SceneObject.h"


RaycastComponent::RaycastComponent(SceneObject* owner) : Component(ComponentID::RAYCAST, owner)
{
}


void RaycastComponent::onHit(const Vector3D& hitDir)
{
	m_Owner->getTransform()->setRotation(hitDir);

	Debugger::Success("Hit");
}
