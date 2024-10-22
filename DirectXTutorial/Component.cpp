#include "Component.h"

Component::Component(ComponentID ID, SceneObject* owner) : id(ID), m_Owner(owner){}

Component::~Component()
{
}