#include "Camera.h"

#include "InputSystem.h"
#include "EngineTime.h"

#include "Debugger.h"

Camera::Camera(const int& refWindowWidth, const int& refWindowHeight) : SceneObject(), 
	ref_windowWidth(refWindowWidth), ref_windowHeight(refWindowHeight)
{
	getTransform()->setPosition(Vector3D(0, 2, -2));

	setActive(true);
	Debugger::Success("[Camera] Instantiated");
}

Camera::~Camera()
{
	setActive(false);
	Debugger::Warning("[Camera] Destroyed");
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
	/* IMPORTANT THIS DOESN'T OVERIDE SCENE OBJECT COMPONENT UPDATES AS OF NOW. SINCE UPDATE IS STILL ON PRIMITIVES AS OF NOW...
	*/

	// [1] VIEW MATRIX
	Matrix4x4 temp;
	Matrix4x4 world_cam;
	world_cam.setIdentity();


	//// MOUSE V ROTATION
	temp.setIdentity();
	temp.setRotationX(m_rotX);
	world_cam *= temp;

	//// MOUSE H ROTATION
	temp.setIdentity();
	temp.setRotationY(m_rotY);
	world_cam *= temp;

	// WASD MOVE CAMERA
	Vector3D dir = world_cam.getZDirection() * m_forward + world_cam.getXDirection() * m_rightward + Vector3D(0, m_upward, 0);
	dir.normalize();
	
	world_cam.setTranslation(getTransform()->getPosition() + (dir * EngineTime::getDeltaTime() * 2));

	
	getTransform()->setWorldMatrix(world_cam);
	m_inversedView = world_cam;
	m_inversedView.inverse();


	// [2] PROJECTION MATRIX
	if (m_IsOrthographic)
		m_proj.setOrthoLH(
			(ref_windowWidth)/100.f,
			(ref_windowHeight)/100.f,
			-50,	//Near plane
			100.f	//Far plane
		);
	else
		m_proj.setPerspectiveFovLH(1.57f, ((float)ref_windowWidth / ref_windowHeight), 0.1f, 100.0f);
}

Matrix4x4 Camera::getProj()
{
	return m_proj;
}

Matrix4x4 Camera::getView()
{
	return m_inversedView;
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

	this->update();
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

	this->update();
}

void Camera::onMouseMove(const Point& mouse_pos)
{
	if (!m_IsFreeLookMode)
		return;

	double deltaTime = EngineTime::getDeltaTime();
	
	float halfHeight = ref_windowHeight / 2.0f;
	float halfWidth = ref_windowWidth / 2.0f;

	//Rotations
	m_rotX += (mouse_pos.y - halfHeight) * deltaTime * 0.1f;
	m_rotY += (mouse_pos.x - halfWidth) * deltaTime * 0.1f;

	//Update matrix
	this->update();

	//Center mouse
	InputSystem::get()->setCursorPosition(Point(halfWidth, halfHeight));
}

void Camera::onLeftMouseDown(const Point& mouse_pos){}
void Camera::onLeftMouseUp(const Point& mouse_pos) {}
void Camera::onRightMouseDown(const Point& mouse_pos) {
	m_IsFreeLookMode = !m_IsFreeLookMode;
	InputSystem::get()->showCursor(!m_IsFreeLookMode);
}
void Camera::onRightMouseUp(const Point& mouse_pos) {}
