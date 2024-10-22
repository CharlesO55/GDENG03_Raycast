#pragma once
#include "ComponentID.h"
class SceneObject;

class Component
{
public:
	Component(ComponentID ID, SceneObject* owner);
	~Component();

	ComponentID id;

	virtual void update() = 0;

protected:
	SceneObject* m_Owner;
};