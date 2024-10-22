#include "ScaleScript.h"

#include "SceneObject.h"

#include "EngineTime.h"

#include <cmath>

ScaleScript::ScaleScript(SceneObject* owner) : Component(ComponentID::ROTATOR, owner)
{
}

void ScaleScript::update()
{
	//m_Owner->getTransform()->m_pos = m_Owner->getTransform()->m_pos.lerp(Vector3D(0), Vector3D(10, 10, 0), (sin(EngineTime::getTotalTime()) + 1) / 2);
	m_Owner->getTransform()->m_scale = m_Owner->getTransform()->m_scale.lerp(Vector3D(1), Vector3D(3*5, 5, 0.1f), (sin(EngineTime::getTotalTime()) + 1) / 2);
}