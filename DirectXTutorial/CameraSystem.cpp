#include "CameraSystem.h"

#include "Debugger.h"

CameraSystem* CameraSystem::Instance = nullptr;

void CameraSystem::init()
{
	if (Instance != nullptr)
		Debugger::Error("[Camera System] Duplication");

	Instance = new CameraSystem();
}

void CameraSystem::createCamera(const int& m_windowWidth, const int& m_windowHeight)
{
	Instance->m_Camera = new Camera(m_windowWidth, m_windowHeight);
}

void CameraSystem::release()
{
	delete Instance->m_Camera;
	delete Instance;
	Instance = nullptr;
	Debugger::Warning("[Camera System] Destroyed");
}

Camera* CameraSystem::getCamera()
{
	return Instance->m_Camera;
}