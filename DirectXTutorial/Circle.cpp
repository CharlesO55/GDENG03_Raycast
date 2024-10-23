#include "Circle.h"

#include "EngineTime.h"
#include <cmath>

Circle::Circle() : Primitive()
{
	Vector3D origin = Vector3D(0);

	float angle;
	float PI = 3.141592653589793;
	int numberOfPoints = 16;

	// VERTICES
	m_verts.push_back({ origin, origin, Vector3D(1), Vector3D(1) });
	for (float i = 0; i < 2; i += 2.f / numberOfPoints) {
		angle = PI * i;
		float x = cos(angle);
		float y = sin(angle);
		m_verts.push_back({ Vector3D(x, y), Vector3D(x, y), Vector3D(x, y), Vector3D(x, y) });
	}
	
	// INDICES
	// LAST TRIANGLE
	m_indices.push_back(0);
	m_indices.push_back(1);
	m_indices.push_back(m_verts.size() - 1);

	// DRAW IN CLOCKWISE MANNER
	for (int i = 1; i < m_verts.size(); i++) {
		m_indices.push_back(0);
		m_indices.push_back(m_verts.size() - i);
		m_indices.push_back(m_verts.size() - i - 1);
	}

	// RANDOMIZE DIRECTION
	Vector3D randDir = Vector3D(((std::rand() % 50) + 50) / 100.f, ((std::rand() % 50) + 50) / 100.f);
	moveDir.x = std::rand() % 2 ? randDir.x * -1 : randDir.x;
	moveDir.y = std::rand() % 2 ? randDir.y * -1 : randDir.y;
}

void Circle::update()
{
	Primitive::update();

	this->getTransform()->move(this->moveDir * EngineTime::getDeltaTime());

	// THIS IS DONE AFTER THE updateMatrix()
	Matrix4x4 screenCheck = this->m_cc.m_world;
	screenCheck *= m_cc.m_view;
	screenCheck *= m_cc.m_proj;

	//Extract the x and y relative to the screen space
	Vector3D screenLoc = screenCheck.getTranslation();

	
	// REVERSE DIRECTION WHEN OUT OF BOUNDS
	if (screenLoc.x + radius > 1)			this->moveDir.x = -1;
	else if (screenLoc.x - radius < -1)		this->moveDir.x = 1;
	else if (screenLoc.y + radius > 1)		this->moveDir.y = -1;
	else if (screenLoc.y - radius < -1)		this->moveDir.y = 1;
}