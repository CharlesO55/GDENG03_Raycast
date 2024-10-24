#pragma once
#include "Matrix4x4.h"

#include "Component.h"
#include "Transformation.h"

#include <vector>

class SceneObject
{
public:
	SceneObject();
	~SceneObject();

	void setChild(SceneObject* child);

	bool tryGetComponent(ComponentID ID, Component*& result);
	Transformation* getTransform();

protected:
	SceneObject* m_child = nullptr;
	std::vector<Component*> m_Components = {};
};