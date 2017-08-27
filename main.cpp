#pragma once
#include "Core.h"
#include "Window.h"
#include "TextureAtlas.h"

void main()
{	
	TextureAtlas* textureAtlas = new TextureAtlas();
	textureAtlas->LoadTextureAtlas("Textures/dirt.png",64,64,64,64);
	Window* window = new Window("MineC++",1280, 720);

	Core* game = new Core(window);
	game->Init();

	system("paused");
}