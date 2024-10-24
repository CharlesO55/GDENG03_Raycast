#pragma once
#include "Camera.h"

class CameraSystem
{
private:
	Camera* m_Camera;
	static CameraSystem* Instance;

public:
	static void init();
	static void createCamera(const int& m_windowWidth, const int& m_windowHeight);
	static void release();

	static Camera* getCamera();
};