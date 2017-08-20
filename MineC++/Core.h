#pragma once

#include <stdio.h>
#include <stdlib.h>

struct GLFWwindow;
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

