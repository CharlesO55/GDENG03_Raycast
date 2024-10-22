#include "ScaleScript.h"

#include "SceneObject.h"

#include "EngineTime.h"

#include <cmath>

ScaleScript::ScaleScript(SceneObject* owner) : Component(ComponentID::ROTATOR, owner)
{
}

void ScaleScript::update()
{
	m_Owner->getTransform()->setScale(
		Vector3D::lerp(Vector3D(1), Vector3D(3 * 5, 5, 0.1f), (sin(EngineTime::getTotalTime()) + 1) / 2)
	);

	
}