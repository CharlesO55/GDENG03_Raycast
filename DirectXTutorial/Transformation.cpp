#include "Transformation.h"


Transformation::Transformation(SceneObject* owner) : Component(ComponentID::TRANSFORMATION, owner)
{
	m_transformation.setIdentity();
}

Transformation::~Transformation()
{
}

void Transformation::scale(Vector3D deltaScale)
{
	m_scale = m_scale + deltaScale;
}

void Transformation::rotate(Vector3D deltaRot)
{
	m_rot = m_rot + deltaRot;
}

void Transformation::move(Vector3D deltaPos)
{
	m_pos = m_pos + deltaPos;
}

void Transformation::update()
{
	Matrix4x4 temp;

	//Reset
	m_transformation.setIdentity();
	
	//Scale
	m_transformation.setScale(m_scale);

	//Rotate
	temp.setIdentity();
	temp.setRotationZ(m_rot.z);
	m_transformation *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot.y);
	m_transformation *= temp;

	temp.setIdentity();
	temp.setRotationX(m_rot.x);
	m_transformation *= temp;

	//Translate
	temp.setIdentity();
	temp.setTranslation(m_pos);
	m_transformation *= temp;
	// Calc local transforms... ^
}