#pragma once
#include "Component.h"

#include "Vector3D.h"

class ScaleScript : public Component
{
public:
	ScaleScript(SceneObject* owner);

	void update() override;
};