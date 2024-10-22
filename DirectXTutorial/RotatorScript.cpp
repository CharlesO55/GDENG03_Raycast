#include "RotatorScript.h"

#include "SceneObject.h"

#include "EngineTime.h"

RotatorScript::RotatorScript(SceneObject* owner) : Component(ComponentID::ROTATOR, owner)
{
	m_rotSpeed = Vector3D(std::rand() % 5, std::rand() % 5, std::rand() % 5);
}

void RotatorScript::update()
{
	m_Owner->getTransform()->rotate(m_rotSpeed * EngineTime::getDeltaTime());
}