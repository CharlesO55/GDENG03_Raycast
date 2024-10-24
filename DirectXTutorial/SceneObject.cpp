#include "SceneObject.h"

SceneObject::SceneObject(){
	m_Components = {new Transformation(this)};
}

SceneObject::~SceneObject(){
	while (m_Components.size() > 0) {
		delete m_Components.back();
		m_Components.pop_back();
	}
}

void SceneObject::setChild(SceneObject* child)
{
	this->m_child = child;
}


bool SceneObject::tryGetComponent(ComponentID ID, Component*& result)
{
	for (int i = 0; i < m_Components.size(); i++) {
		if (m_Components[i]->id == ID) {
			result = m_Components[i];
			return true;
		}
	}

	return false;
}

Transformation* SceneObject::getTransform()
{
	return (Transformation*)this->m_Components[0];
}