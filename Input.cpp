#include "Input.h"

Input* Input::_instance = nullptr;

Input::Input()
{

}

Input* Input::Instance()
{
	if (_instance == nullptr)
		_instance = new Input();
	return _instance;
}

void Input::SetMousePosition(double x, double y)
{
	_window->SetCursorPosition(x, y);
}

void Input::SetKeyTrue(int key)
{
	if (!_keys[key])
	{
		_keys[key] = true;
		_previousKeys[key] = true;
	}
}

void Input::SetKeyFalse(int key)
{
	_keys[key] = false;
}

void Input::ClearKeyBuffer()
{
	memset(&_previousKeys, false, 1024);
}

bool Input::GetKeyPressed(uint16 key)
{
	return _previousKeys[key];
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


