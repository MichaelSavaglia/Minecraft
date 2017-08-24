#pragma once
#include "Window.h"

class Input
{
	friend Window;
	friend GLFWwindow;
private:
	double _mouseX;
	double _mouseY;
	double _mouseWheelX;
	double _mouseWheelY;

	bool _keys[1024];
	bool _mouseButtons[32];

	Window* _window;

	static Input* _instance;
public:
	Input();
	~Input();
	static Input* Instance();
public:
	void SetMousePosition(double x, double y) { _window->SetCursorPosition(x, y); }

private:
	inline void RegisterWindow(Window* window) { _window = window; }
};



