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

bool TextureAtlas::LoadTextureAtlas(std::string path, int tileWidth, int tileHeight, int imageWidth, int imageHeight)
{
	mTexturePath	= path;
	mTileWidth		= tileWidth;
	mTileHeight		= tileHeight;
	mImageWidth		= imageWidth;
	mImageHeight	= imageHeight;

	auto channelcount = 0;
	auto var = SOIL_load_image(path.c_str(), &mImageWidth, &imageHeight, &channelcount, 0);

	auto imageSize = channelcount * 24 * imageWidth * imageHeight;

	auto str = std::string((const char*)var);

	printf(str.c_str());

	GLuint mTexture = SOIL_load_OGL_texture
	(
		path.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	return true;

}

bool TextureAtlas::Reload()
{
	if (mTexturePath != "")
	{
		return LoadTextureAtlas(mTexturePath, mTileWidth, mTileHeight, mImageWidth, mImageHeight);
	}
	return false;
}
