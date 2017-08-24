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
	uint16			_width;
	uint16			_height;

	GLFWwindow*		_window;
	Input*			_input;

public:
	Window(StringPtr title, uint16 windowWidth, uint16 windowHeight);
	~Window();

	void SetWindowTitle(StringPtr title);

	inline uint16& GetWindowWidth()		noexcept { return _width;  }
	inline uint16& GetWindowHeight()	noexcept { return _height; }
	inline GLFWwindow* GetGLFWWindow()	const noexcept { return _window; }

private:
	void SetCursorPosition(double posX, double posY);

private:
	friend static void CallbackClosed(GLFWwindow* glfwWindow);
	friend static void CallbackIconified(GLFWwindow* glfwWindow, int iconified);
	friend static void CallbackWindowResize(GLFWwindow* glfwWindow, uint16 width, uint16 height);
	friend static void CallbackKeyPress(GLFWwindow* glfwWindow, int key, int code, int action, int mods);
	friend static void CallbackMouseButtonPressed(GLFWwindow* glfwWindow, int button, int action, int mods);
	friend static void CallbackScrollCallBack(GLFWwindow* glfwWindow, double xoffset, double yoffset);
	friend static void CallbackMouseLocation(GLFWwindow* glfwWindow, double xpos, double ypos);
	friend static void CallbackFrameBufferResized(GLFWwindow * glfwWindow, int width, int height);

private:
	void UpdateKeyboardState(int key, int code, int action, int mods);
	void UpdateMouseButtonState(int button, int action, int mods);
	void UpdateMousePosition(double xpos, double ypos);
	void UpdateMouseScroll(double xoffset, double yoffset);
};
