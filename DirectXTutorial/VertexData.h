#pragma once
#include "Vector2D.h"
#include "Vector3D.h"
#include "Matrix4x4.h"




struct vertexTex {
	Vector3D position;
	Vector2D texcoord;
};


struct vertexColor {
	Vector3D position;
	Vector3D position1;
	Vector3D color;
	Vector3D color1;
};


__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	double m_time;
};