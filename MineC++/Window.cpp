//#include "Types.h"
//#include <glew.h>
//#include <glfw3.h>
//#include <vector>
//#include <future>
//#include "Window.h"
//
//
//Window::Window(StringPointer title, Uint16 windowWidth, Uint16 windowHeight)
//{
//	_input = Input::Instance();
//}
//
//Window::~Window()
//{
//
//}
//
//void Window::UpdateKeyboardState(int key, int code, int action, int mods)
//{
//	_input->_keys[key] = action != GLFW_RELEASE;
//}
//
//void Window::UpdateMouseButtonState(int button, int action, int mods)
//{
//	_input->_mouseButtons[button] = action != GLFW_RELEASE;
//}
//
//void Window::UpdateMousePosition(double xpos, double ypos)
//{
//	_input->_mouseX = xpos;
//	_input->_mouseY = ypos;
//}
//
//void Window::UpdateMouseScroll(double xoffset, double yoffset)
//{
//	_input->_mouseWheelX = xoffset;
//	_input->_mouseWheelY = yoffset;
//}
//
//void Window::ExecuteClosedCallbacks(Window* window)
//{
//	window->OnWindowClose->Execute(window);
//}
//
//void Window::SetWindowTitle(StringPointer title)
//{
//	glfwSetWindowTitle(_window, title);
//}
//
//
//void CallbackClosed(GLFWwindow * glfwWindow)
//{
//	Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
//
//	if (glfwWindowShouldClose(glfwWindow) == 1)
//	{
//		window->ExecuteClosedCallbacks(window);
//	}
//}
//
//void CallbackIconified(GLFWwindow* glfwWindow, int iconified)
//{
//	if (iconified)
//		glfwWaitEvents();
//}
//
//void CallbackWindowResize(GLFWwindow* glfwWindow, Uint16 width, Uint16 height)
//{
//	Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
//	window->_width = width;
//	window->_height = height;
//
//	glViewport(0, 0, width, height);
//}
//
//void CallbackKeyPress(GLFWwindow* glfwWindow, int key, int code, int action, int mods)
//{
//	Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
//	window->UpdateKeyboardState(key, code, action, mods);
//}
//
//void CallbackMouseButtonPressed(GLFWwindow* glfwWindow, int button, int action, int mods)
//{
//	Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
//	window->UpdateMouseButtonState(button, action, mods);
//}
//
//void CallbackScrollCallBack(GLFWwindow* glfwWindow, double xoffset, double yoffset)
//{
//	Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
//	window->UpdateMouseScroll(xoffset, yoffset);
//}
//
//void CallbackMouseLocation(GLFWwindow* glfwWindow, double xpos, double ypos)
//{
//	Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
//	window->UpdateMousePosition(xpos,ypos);
//}
//
//void CallbackFrameBufferResized(GLFWwindow* glfwWindow, int width, int height)
//{
//	//To Be Added
//}
//
