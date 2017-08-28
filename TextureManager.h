#pragma once
#include <unordered_map>
#include <SOIL.h>
#include <glfw3.h>
class TextureManager
{
public:
	static TextureManager* Instance()
	{
		static TextureManager *instance = new TextureManager();
		return instance;
	}

	GLuint LoadTexture(const char* path);

	~TextureManager();
private:
	TextureManager();
	std::unordered_map<const char*, GLuint> mTextures;
};

