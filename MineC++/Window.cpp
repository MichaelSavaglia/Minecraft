#include "Input.h"
#include "Window.h"

Input* Input::_instance = nullptr;
Window::Window(StringPtr title, uint16 windowWidth, uint16 windowHeight)
{
	//TODO:: Add Logger To StartUp
	if (!glfwInit())
	{	
		return;
	}
	_window = glfwCreateWindow(1280, 720, "MineC++", NULL, NULL);

	if (_window == NULL) { glfwTerminate(); }

	glfwMakeContextCurrent(_window);
	glewExperimental = true;

	if (glewInit() != GLEW_OK){}

	glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_input = Input::Instance();
	_input->RegisterWindow(this);

}

Window::~Window()
{

}

void Window::UpdateKeyboardState(int key, int code, int action, int mods)
{
	_input->_keys[key] = action != GLFW_RELEASE;
}

void Window::UpdateMouseButtonState(int button, int action, int mods)
{
	_input->_mouseButtons[button] = action != GLFW_RELEASE;
}

void Window::UpdateMousePosition(double xpos, double ypos)
{
	_input->_mousePosition.x = xpos;
	_input->_mousePosition.y = ypos;
}

void Window::UpdateMouseScroll(double xoffset, double yoffset)
{
	_input->_mouseWheel.x = xoffset;
	_input->_mouseWheel.y = yoffset;
}

void Window::SetWindowTitle(StringPtr title)
{
	glfwSetWindowTitle(_window, title);
}

void Window::SetCursorPosition(double posX, double posY)
{
	glfwSetCursorPos(_window, posX, posY);
}

void CallbackClosed(GLFWwindow * glfwWindow)
{
	Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));

	if (glfwWindowShouldClose(glfwWindow) == 1)
	{
		exit(0);
	}
}

void CallbackIconified(GLFWwindow* glfwWindow, int iconified)
{
	if (iconified)
		glfwWaitEvents();
}

void CallbackWindowResize(GLFWwindow* glfwWindow, uint16 width, uint16 height)
{
	Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
	window->_width = width;
	window->_height = height;

	glViewport(0, 0, width, height);
}

void CallbackKeyPress(GLFWwindow* glfwWindow, int key, int code, int action, int mods)
{
	Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
	window->UpdateKeyboardState(key, code, action, mods);
}

void CallbackMouseButtonPressed(GLFWwindow* glfwWindow, int button, int action, int mods)
{
	Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
	window->UpdateMouseButtonState(button, action, mods);
}

void CallbackScrollCallBack(GLFWwindow* glfwWindow, double xoffset, double yoffset)
{
	Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
	window->UpdateMouseScroll(xoffset, yoffset);
}

void CallbackMouseLocation(GLFWwindow* glfwWindow, double xpos, double ypos)
{
	Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
	window->UpdateMousePosition(xpos,ypos);
}

void CallbackFrameBufferResized(GLFWwindow* glfwWindow, int width, int height)
{
	Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
	window->_width = width;
	window->_height = height;
	glViewport(0, 0, width, height);
}




