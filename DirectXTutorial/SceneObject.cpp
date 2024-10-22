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


Component* SceneObject::getComponent(ComponentID ID)
{
	for (int i = 0; i < m_Components.size(); i++) {
		if (m_Components[i]->id == ID)
			return m_Components[i];
	}

	return nullptr;
}

Transformation* SceneObject::getTransform()
{
	return (Transformation*)this->m_Components[0];
}