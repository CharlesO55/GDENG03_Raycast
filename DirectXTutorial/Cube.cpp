#include "Cube.h"

#include "GraphicsEngine.h"
#include "DeviceContext.h"

#include "RotatorScript.h"
#include "ScaleScript.h"


Cube::Cube() : Primitive()
{
	//m_Components.push_back(new RotatorScript(this));
	//m_Components.push_back(new ScaleScript(this));


	m_verts =
	{
		//X - Y - Z
		{Vector3D(-0.5f,-0.5f,-0.5f), Vector3D(-0.5f,-0.5f,-0.5f),   Vector3D(1,0,0),  Vector3D(0.2f,0,0) },
		{Vector3D(-0.5f,0.5f,-0.5f), Vector3D(-0.5f,0.5f,-0.5f),   Vector3D(0,1,0), Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,0.5f,-0.5f), Vector3D(0.5f,0.5f,-0.5f),  Vector3D(0,0,1),  Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,-0.5f,-0.5f), Vector3D(0.5f,-0.5f,-0.5f),    Vector3D(1,0,1), Vector3D(0.2f,0,0) },

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f), Vector3D(0.5f,-0.5f,0.5f),   Vector3D(1,0,0), Vector3D(0,0.2f,0) },
		{ Vector3D(0.5f,0.5f,0.5f), Vector3D(0.5f,0.5f,0.5f),   Vector3D(0,1,0), Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,0.5f,0.5f), Vector3D(-0.5f,0.5f,0.5f),  Vector3D(0,0,1),  Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,-0.5f,0.5f), Vector3D(-0.5f,-0.5f,0.5f),    Vector3D(0,1,1), Vector3D(0,0.2f,0) }

	};

	m_indices =
	{
		//FRONT SIDE
		0,1,2,  
		2,3,0,  
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};
}



Cube::Cube(Vector3D color)
{
	m_Components.push_back(new RotatorScript(this));

	m_verts =
	{
		//X - Y - Z
		{ Vector3D(-0.5f,-0.5f,-0.5f), Vector3D(-0.5f,-0.5f,-0.5f),   color, color },
		{ Vector3D(-0.5f,0.5f,-0.5f), Vector3D(-0.5f,0.5f,-0.5f),   color, color },
		{ Vector3D(0.5f,0.5f,-0.5f), Vector3D(0.5f,0.5f,-0.5f),  color, color },
		{ Vector3D(0.5f,-0.5f,-0.5f), Vector3D(0.5f,-0.5f,-0.5f),    color, color },

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f), Vector3D(0.5f,-0.5f,0.5f),   color, color },
		{ Vector3D(0.5f,0.5f,0.5f), Vector3D(0.5f,0.5f,0.5f),   color, color },
		{ Vector3D(-0.5f,0.5f,0.5f), Vector3D(-0.5f,0.5f,0.5f),  color, color },
		{ Vector3D(-0.5f,-0.5f,0.5f), Vector3D(-0.5f,-0.5f,0.5f),    color, color }

	};

	m_indices =
	{
		//FRONT SIDE
		0,1,2,
		2,3,0,
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};
}

Cube::~Cube()
{
	release();
}