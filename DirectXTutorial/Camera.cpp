#include "Camera.h"

#include "InputSystem.h"
#include "EngineTime.h"

#include <iostream>

Camera::Camera(int* refWindowWidth, int* refWindowHeight) : ref_windowWidth(refWindowWidth), ref_windowHeight(refWindowHeight), SceneObject()
{
	m_view.setIdentity();
	m_view.setTranslation(Vector3D(0, 2, -2));

	setActive(true);
}

Camera::~Camera()
{
	delete ref_windowHeight, ref_windowWidth;
}

void Camera::setActive(bool active)
{
	if (active)
		InputSystem::get()->addListener(this);
	else
		InputSystem::get()->removeListener(this);
}

void Camera::update()
{
	Matrix4x4 temp;
	Matrix4x4 world_cam;
	world_cam.setIdentity();

	// MOUSE V ROTATION
	temp.setIdentity();
	temp.setRotationX(m_rotX);
	world_cam *= temp;

	// MOUSE H ROTATION
	temp.setIdentity();
	temp.setRotationY(m_rotY);
	world_cam *= temp;

	// WASD MOVE CAMERA
	Vector3D new_pos = m_view.getTranslation() + world_cam.getZDirection() * (m_forward * 0.1f);
	new_pos = new_pos + world_cam.getXDirection() * (m_rightward * 0.1f);
	new_pos.y += (m_upward * 0.1f);
	world_cam.setTranslation(new_pos);

	m_view = world_cam;

	if (m_IsOrthographic)
		m_proj.setOrthoLH(
			(*ref_windowWidth)/100,
			(*ref_windowHeight)/100,
			-50,	//Near plane
			100.0f	//Far plane
		);
	else
		m_proj.setPerspectiveFovLH(1.57f, ((float)*ref_windowWidth / (float)*ref_windowHeight), 0.1f, 100.0f);
}

Matrix4x4 Camera::getProj()
{
	return m_proj;
}

Matrix4x4 Camera::getView()
{
	Matrix4x4 inverse = m_view;
	inverse.inverse();
	return inverse;
}

void Camera::onKeyDown(int key)
{
	switch (key) {
	case 'W':
		m_forward = 1;
		break;
	case 'S':
		m_forward = -1;
		break;
	case 'D':
		m_rightward = 1;
		break;
	case 'A':
		m_rightward = -1;
		break;
	case 'Q':
		m_upward = 1;
		break;
	case 'E':
		m_upward = -1;
		break;
	}
}

void Camera::onKeyUp(int key)
{
	m_forward = 0;
	m_rightward = 0;
	m_upward = 0;

	switch (key) {
		case 'P':
			m_IsOrthographic = !m_IsOrthographic;
	}
}

void Camera::onMouseMove(const Point& mouse_pos)
{
	double deltaTime = EngineTime::getDeltaTime();
	m_rotX += (mouse_pos.y - (*ref_windowHeight/ 2.0f)) * deltaTime * 0.1f;
	m_rotY += (mouse_pos.x - (*ref_windowWidth / 2.0f)) * deltaTime * 0.1f;
}

void Camera::onLeftMouseDown(const Point& mouse_pos)
{
}

void Camera::onLeftMouseUp(const Point& mouse_pos)
{
}

void Camera::onRightMouseDown(const Point& mouse_pos)
{
}

void Camera::onRightMouseUp(const Point& mouse_pos)
{
}
