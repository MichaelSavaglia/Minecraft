#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

#include <glew.h>
#include <glfw3.h>


class Core
{
public:
	Core();
	~Core();

	bool Init();
	virtual void LoadObjects();
	void MainLoop();

	virtual void Draw();
	virtual void Update();
	virtual void Input();


private:

	GLFWwindow* window;
};

