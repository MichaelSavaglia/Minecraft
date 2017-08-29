#pragma once
#include "Core.h"
#include "Window.h"
void main()
{	
	Window* window = new Window("MineC++",1280, 720);

	Core* game = new Core(window);
	game->Init();

	system("paused");
}