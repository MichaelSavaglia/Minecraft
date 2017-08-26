#include "Input.h"

Input::Input()
{

}

Input * Input::Instance()
{
	if (_instance == nullptr)
		_instance = new Input();
	return _instance;
}

void Input::SetMousePosition(double x, double y)
{
	_window->SetCursorPosition(x, y);
}

bool Input::GetKeyPressed(uint16 key)
{
	return _keys[key];
}

bool Input::GetMouseButtonPressed(uint16 key)
{
	return _mouseButtons[key];
}

const glm::vec2& Input::GetMousePosition()
{
	return _mousePosition;
}

const glm::vec2 & Input::GetMouseWheelValues()
{
	return _mouseWheel;
}

