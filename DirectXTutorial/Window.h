#pragma once
#include <Windows.h>



class Window
{
public:
	Window();
	~Window();

	bool Run();

	RECT getClientWindowRect();

	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();
	virtual void onFocus();
	virtual void onKillFocus();

	void CalcWindowRect();

private:
	bool broadcast();
	float timePerFrame = 1 / 60.0f;

protected:
	HWND m_hwnd;
	bool m_is_run;
	bool m_is_init = false;

	int m_windowWidth;
	int m_windowHeight;
};