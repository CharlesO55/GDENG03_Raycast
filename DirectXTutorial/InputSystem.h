#pragma once
#include "InputListener.h"
#include <unordered_set>

#include "Vector3D.h"
#include "Point.h"

class InputSystem
{
private:
	InputSystem();
	~InputSystem();

	static InputSystem* m_system;

public:
	void update();
	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);

	Point getCursorPos();
	void setCursorPosition(const Point& pos);
	void showCursor(bool show);

public:
	static InputSystem* get();
	static void create();
	static void release();

private:
	std::unordered_set<InputListener*> m_set_listeners;
	unsigned char m_keys_state[256] = {};
	unsigned char m_old_keys_state[256] = {};

	Point m_cursor_pos;
	Point m_old_mouse_pos;
	bool m_first_time = true;
};