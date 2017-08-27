#pragma once
#include <string>
#include <vector>
class Texture
{
private:
	int mWidth;
	int mHeight;

	unsigned const char* data[];

};
class TextureAtlas
{
private:
	std::vector<Texture> mTextures;
	std::string mTexturePath;
	int mTileWidth;
	int mTileHeight;
	int mImageWidth;
	int mImageHeight;

	GLuint mTexture;


	GLuint mDirtTexture() { return mTexture; }
public:
	TextureAtlas();
	~TextureAtlas();


	bool LoadTextureAtlas(std::string path,int tileWidth, int tileHeight, int imageWidth, int imageHeight);
	bool Reload();
};

