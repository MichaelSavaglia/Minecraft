#pragma once
#include <string>
class TextureAtlas
{
private:
	std::string mTexturePath;
	std::size_t mTileWidth;
	std::size_t mTileHeight;
	std::size_t mImageWidth;
	std::size_t mImageHeight;

public:
	TextureAtlas();
	~TextureAtlas();


	void LoadTextureAtlas(std::string path, size_t tileWidth, size_t tileHeight, size_t imageWidth, size_t imageHeight);
	void Reload();
};

