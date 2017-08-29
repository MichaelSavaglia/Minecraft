#pragma once
#include <glew.h>
#include <glfw3.h>
#include <vector>
#include <future>
#include "Types.h"

class Input;

class Window
{
	friend Input;
private:
	StringPtr		_title;
	int				_width;
	int				_height;

	GLFWwindow*		_window;
	Input*			_input;

public:
	Window(StringPtr title, uint16 windowWidth, uint16 windowHeight);
	~Window();

	void SetWindowTitle(StringPtr title);

	inline int& GetWindowWidth()		noexcept { return _width;  }
	inline int& GetWindowHeight()		noexcept { return _height; }
	inline GLFWwindow* GetGLFWWindow()	const noexcept { return _window; }

private:
	void SetCursorPosition(double posX, double posY);

private:
	friend static void CallbackClosed(GLFWwindow* glfwWindow);
	friend static void CallbackIconified(GLFWwindow* glfwWindow, int iconified);
	friend static void CallbackWindowResize(GLFWwindow* glfwWindow, int width, int height);
	friend static void CallbackKeyPress(GLFWwindow* glfwWindow, int key, int code, int action, int mods);
	friend static void CallbackMouseButtonPressed(GLFWwindow* glfwWindow, int button, int action, int mods);
	friend static void CallbackScrollPosition(GLFWwindow* glfwWindow, double xoffset, double yoffset);
	friend static void CallbackMouseLocation(GLFWwindow* glfwWindow, double xpos, double ypos);
	friend static void CallbackFrameBufferResized(GLFWwindow * glfwWindow, int width, int height);

private:
	void UpdateKeyboardState(int key, int code, int action, int mods);
	void UpdateMouseButtonState(int button, int action, int mods);
	void UpdateMousePosition(double xpos, double ypos);
	void UpdateMouseScroll(double xoffset, double yoffset);
};
