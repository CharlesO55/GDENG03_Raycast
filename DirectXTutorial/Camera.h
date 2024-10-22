#pragma once
#include "Matrix4x4.h"


#include "InputListener.h"
#include "SceneObject.h"

class Camera : public InputListener, public SceneObject
{
public:
	Camera(int* refWindowWidth, int* refWindowHeight);
	~Camera();

	void setActive(bool active);
	void update();

	Matrix4x4 getView();
	Matrix4x4 getProj();


private:
	Matrix4x4 m_view;
	Matrix4x4 m_proj;


	int* ref_windowWidth = nullptr;
	int* ref_windowHeight = nullptr;
	

	//DIRECTIONAL MOVEMENT
	int m_rightward = 0;
	int m_forward = 0;
	int m_upward = 0;

	float m_rotX = 0;
	float m_rotY = 0;

	bool m_IsOrthographic = false;

// Inherited via InputListener
private:
	void onKeyDown(int key) override;
	void onKeyUp(int key) override;

	void onMouseMove(const Point& mouse_pos) override;

	void onLeftMouseDown(const Point& mouse_pos) override;
	void onLeftMouseUp(const Point& mouse_pos) override;
	void onRightMouseDown(const Point& mouse_pos) override;
	void onRightMouseUp(const Point& mouse_pos) override;
};