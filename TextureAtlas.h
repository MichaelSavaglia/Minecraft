#pragma once
#include <string>
#include <map>
#include <glm.hpp>
#include "BlockTypeEnum.h"

using BlockTextureData = glm::vec3;

class TextureAtlas
{
private:
	std::map<BlockType, BlockTextureData> mBlockData;
	GLuint mTexture;
	int mRowCount;

	std::string mPath;
public:
	static TextureAtlas* Instance()
	{
		static TextureAtlas *instance = new TextureAtlas("Textures/TextureAtlas.png", 6);
		return instance;
	}
	BlockTextureData GetBlockByType(BlockType type);
private:
	TextureAtlas(std::string path, uint8 rowSize);
	~TextureAtlas();

	

private:
	float GetTextureXOffset(int index);
	float GetTextureYOffset(int index);

public:
	inline const GLuint GetTexture() const noexcept { return mTexture; }

	void ReloadTextureAtlas();
};

