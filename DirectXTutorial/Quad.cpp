#include "Quad.h"

#include "GraphicsEngine.h"


Quad::Quad() : Primitive()
{
	m_verts = {
		{ Vector3D(-0.75f,-0.5f,-0.5f), Vector3D(-0.5f,-0.5f,-0.5f),   Vector3D(1,0,0),  Vector3D(0.2f,0,0) }, //BL
		{ Vector3D(-0.5f,0.5f,-0.5f), Vector3D(-0.5f,0.5f,-0.5f),   Vector3D(0,1,0), Vector3D(0.2f,0.2f,0) }, //TL
		{ Vector3D(0.75f,0.5f,-0.5f), Vector3D(0.5f,0.5f,-0.5f),  Vector3D(0,0,1),  Vector3D(0.2f,0.2f,0) },	//TR
		{ Vector3D(0.5f,-0.5f,-0.5f), Vector3D(0.5f,-0.5f,-0.5f),    Vector3D(1,1,1), Vector3D(0.2f,0,0) }  //BR
	};

	m_indices = {
		0, 1, 2,
		2, 3, 0
	};
}