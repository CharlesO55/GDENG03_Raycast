#include "AppWindow.h"
#include "InputSystem.h"
#include "EngineTime.h"
#include "Debugger.h"

int main()
{
	try
	{
		GraphicsEngine::create();
		InputSystem::create();
		EngineTime::create();
	}
	catch (...) { return -1; }
	{
		try
		{
			AppWindow app;
			while (app.Run()) {
			}
		}
		catch (...) {
			InputSystem::release();
			GraphicsEngine::release();
			EngineTime::release();
			return -1;
		}
	}


	InputSystem::release();
	GraphicsEngine::release();
	EngineTime::release();

	return 0;
}