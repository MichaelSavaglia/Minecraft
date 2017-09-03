#include "TextureManager.h"




TextureManager::TextureManager()
{

}

GLuint TextureManager::LoadTexture(std::string path)
{
	auto id = mTextures.count(path);
	if (id == 0)
	{

		id = SOIL_load_OGL_texture(
			path.c_str(),
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS
		);
		mTextures.insert({ path, id });
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
