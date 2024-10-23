#include "RotatorScript.h"

#include "SceneObject.h"

#include "EngineTime.h"

RotatorScript::RotatorScript(SceneObject* owner) : Component(ComponentID::ROTATOR, owner)
{
	m_rotSpeed = Vector3D(20 * 0.0174533f, 5 * 0.0174533f, 30 * 0.0174533f);
}

void RotatorScript::update()
{
	m_Owner->getTransform()->rotate(m_rotSpeed * EngineTime::getDeltaTime());
}