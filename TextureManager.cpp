#include "TextureManager.h"




TextureManager::TextureManager()
{

}

GLuint TextureManager::LoadTexture(const char * path)
{
	auto id = mTextures[path];
	if (!id)
	{

		id = SOIL_load_OGL_texture(
			path,
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
		);
		mTextures.insert({ path, id });
	}
	return id;
	//auto search = mTextures.find(path);
	//if (search != mTextures.end())
	//{
	//	return search->second;
	//}
	//else
	//{
	//	auto id = SOIL_load_OGL_texture(
	//		path,
	//		SOIL_LOAD_AUTO,
	//		SOIL_CREATE_NEW_ID,
	//		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
	//	);
	//	mTextures.insert({ path, id });
	//	return id;
	//}
}

GLuint TextureManager::GetTexture(const char * path)
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
