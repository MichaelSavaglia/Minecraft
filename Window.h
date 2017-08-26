//#pragma once
//
//class Input;
//class WindowEventHandeler;
//
//class Window
//{
//	friend WindowEventHandeler;
//	friend Input;
//private:
//	StringPointer	_title;
//	Uint16			_width;
//	Uint16			_height;
//
//	GLFWwindow*		_window;
//	Input*			_input;
//
//public:
//	WindowEventHandeler* OnWindowClose;
//
//public:
//	Window(StringPointer title, Uint16 windowWidth, Uint16 windowHeight);
//	~Window();
//
//	void SetWindowTitle(StringPointer title);
//
//	inline Uint16& GetWindowWidth()		noexcept { return _width;  } 
//	inline Uint16& GetWindowHeight()	noexcept { return _height; }
//	inline GLFWwindow* GetGLFWWindow()	const noexcept { return _window; }
//
//private:
//	friend static void CallbackClosed(GLFWwindow* glfwWindow);
//	friend static void CallbackIconified(GLFWwindow* glfwWindow, int iconified);
//	friend static void CallbackWindowResize(GLFWwindow* glfwWindow, Uint16 width, Uint16 height);
//	friend static void CallbackKeyPress(GLFWwindow* glfwWindow, int key, int code, int action, int mods);
//	friend static void CallbackMouseButtonPressed(GLFWwindow* glfwWindow, int button, int action, int mods);
//	friend static void CallbackScrollCallBack(GLFWwindow* glfwWindow, double xoffset, double yoffset);
//	friend static void CallbackMouseLocation(GLFWwindow* glfwWindow, double xpos, double ypos);
//	friend static void CallbackFrameBufferResized(GLFWwindow * glfwWindow, int width, int height);
//
//private:
//	void UpdateKeyboardState(int key, int code, int action, int mods);
//	void UpdateMouseButtonState(int button, int action, int mods);
//	void UpdateMousePosition(double xpos, double ypos);
//	void UpdateMouseScroll(double xoffset, double yoffset);
//
//	void ExecuteClosedCallbacks(Window* window);
//};
//
//class WindowEventHandeler
//{
//	friend Window;
//	friend GLFWwindow;
//private:
//	std::vector<std::function<void(Window*)>> _callbacks;
//private:
//	void Execute(Window* window)
//	{
//		for (auto const &callback : _callbacks)
//			callback(window);
//	}
//public:
//	void operator+=(const std::function<void(Window*)> rhs)
//	{
//		_callbacks.push_back(rhs);
//	}
//};
//
//
//class Input
//{
//	friend Window;
//	friend GLFWwindow;
//private:
//	double _mouseX;
//	double _mouseY;
//	double _mouseWheelX;
//	double _mouseWheelY;
//
//	bool _keys[1024];
//	bool _mouseButtons[32];
//
//	static Input* _instance;
//public:
//	static Input* Instance()
//	{
//		if (_instance == nullptr)
//			_instance = new Input();
//		return _instance;
//	}
//};
//Input* Input::_instance = nullptr;
//
