#include "TextureManager.h"




TextureManager::TextureManager()
{

}

GLuint TextureManager::LoadTexture(std::string path, bool invertY)
{
	auto count = mTextures.count(path);
	if (count == 0)
	{
		GLuint id = 0;

		if (!invertY)
		{
			id = SOIL_load_OGL_texture(
				path.c_str(),
				SOIL_LOAD_AUTO,
				SOIL_CREATE_NEW_ID,
				SOIL_FLAG_MIPMAPS
			);
		}
		
		else
		{
			id = SOIL_load_OGL_texture(
				path.c_str(),
				SOIL_LOAD_AUTO,
				SOIL_CREATE_NEW_ID,
				SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
			);
		}

		mTextures.insert({ path, id });
	}
	return mTextures[path];
}

GLuint TextureManager::ReloadTexture(GLuint id, std::string path, bool invertY)
{
	auto count = mTextures.count(path);
	if (count == 1)
	{
		GLuint id = 0;

		if (!invertY)
		{
			id = SOIL_load_OGL_texture(
				path.c_str(),
				SOIL_LOAD_AUTO,
				SOIL_CREATE_NEW_ID,
				SOIL_FLAG_MIPMAPS
			);
		}
		else
		{
			id = SOIL_load_OGL_texture(
				path.c_str(),
				SOIL_LOAD_AUTO,
				SOIL_CREATE_NEW_ID,
				SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
			);
		}

		mTextures[path] = id;
	}
	return mTextures[path];

}
GLuint TextureManager::GetTexture(std::string path)
{
	auto id = mTextures[path];
	if (id)
		return id;
	printf("Could not find texture %s", path);
	return -1;
	
}

TextureManager::~TextureManager()
{

}
