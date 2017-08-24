#pragma once
#include "Core.h"
#include "Window.h"

void onWindowClosed(Window* window)
{
	printf("Window Closed");
}
void main()
{
	Window* window = new Window("MineC++",1280, 720);

	Core* game = new Core(window);
	game->Init();

	system("paused");
}