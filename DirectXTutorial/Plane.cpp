#include "Plane.h"

Plane::Plane()
{
	m_verts = {
		{ Vector3D(-1,0,-1), Vector3D(-1,0,-1),   Vector3D(1,0,0), Vector3D(1,0,0) }, //BL
		{ Vector3D(-1,0,1), Vector3D(-1,0,1),   Vector3D(0,1,0), Vector3D(0,1,0) }, //TL
		{ Vector3D(1, 0, 1), Vector3D(1, 0, 1),  Vector3D(0,0,1),  Vector3D(0,0,1) },	//TR
		{ Vector3D(1, 0, -1), Vector3D(1, 0, -1),    Vector3D(1,1,0), Vector3D(1,1,0) }  //BR
	};

	// Draw on both sides
	m_indices = {
		0, 1, 2,
		2, 3, 0,
		2, 1, 0,
		0, 3, 2
	};
}

Plane::Plane(Vector3D color)
{
	m_verts = {
		{ Vector3D(-1,0,-1), Vector3D(-1,0,-1),   color, color }, //BL
		{ Vector3D(-1,0,1), Vector3D(-1,0,1),   color, color }, //TL
		{ Vector3D(1, 0, 1), Vector3D(1, 0, 1),  color, color },	//TR
		{ Vector3D(1, 0, -1), Vector3D(1, 0, -1),    color, color }  //BR
	};

	// Draw on both sides
	m_indices = {
		0, 1, 2,
		2, 3, 0,
		2, 1, 0,
		0, 3, 2
	};
}


Plane::~Plane()
{
	release();
}
