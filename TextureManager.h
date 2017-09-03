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

	GLuint LoadTexture(std::string path, bool invertY = false);
	GLuint ReloadTexture(GLuint id, std::string path, bool invertY = false);
	GLuint GetTexture(std::string path);

	~TextureManager();
private:
	TextureManager();
	std::unordered_map<std::string, GLuint> mTextures;
};

