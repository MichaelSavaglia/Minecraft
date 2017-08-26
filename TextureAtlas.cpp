#include <SOIL.h>
#include <glew.h>
#include <glfw3.h>
#include "TextureAtlas.h"



TextureAtlas::TextureAtlas()
{
}


TextureAtlas::~TextureAtlas()
{
}

void TextureAtlas::LoadTextureAtlas(std::string path, size_t tileWidth, size_t tileHeight, size_t imageWidth, size_t imageHeight)
{
	mTexturePath = path;
	mTileWidth = tileWidth;
	mTileHeight = tileHeight;
	mImageWidth = imageWidth;
	mImageHeight = imageHeight;

	GLuint tex_2d = SOIL_load_OGL_texture
	(
		path.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

}

void TextureAtlas::Reload()
{
	if (mTexturePath != "")
	{
		LoadTextureAtlas(mTexturePath, mTileWidth, mTileHeight, mImageWidth, mImageHeight);
	}
}
