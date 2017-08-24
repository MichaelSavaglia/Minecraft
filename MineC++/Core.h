#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "Dependencies\soil\SOIL.h"
#include "Window.h"

class Core
{
public:
	Core(Window* window);
	~Core();

	bool Init();
	virtual void LoadObjects();
	void MainLoop();

	virtual void Draw();
	virtual void Update();
	virtual void Input();


private:
	Window* _window;
};

