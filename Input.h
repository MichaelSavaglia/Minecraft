#pragma once
#include "Window.h"
#include <glm.hpp>
class Input
{
	friend Window;
	friend GLFWwindow;
private:
	glm::vec2 _mousePosition;
	glm::vec2 _mouseWheel;

	bool _keys[1024]{false};
	bool _previousKeys[1024]{false};



	bool _mouseButtons[32];

	Window* _window;

	static Input* _instance;
public:
	Input();
	~Input();
	static Input* Instance();
public:
	void SetMousePosition(double x, double y);
	void ClearKeyBuffer();

	bool GetKeyPressed(int key);
	bool GetKeyDown(int key);
	bool GetKeyUp(int key);

	bool GetMouseButtonPressed(uint16 key);
	const glm::vec2& GetMousePosition();
	const glm::vec2& GetMouseWheelValues();

private:
	inline void RegisterWindow(Window* window) { _window = window; }
	void SetKeyTrue(int key);
	void SetKeyFalse(int key);
};



