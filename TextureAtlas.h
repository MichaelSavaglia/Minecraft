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
public:
	TextureAtlas(std::string path, uint8 rowSize);
	~TextureAtlas();

	const BlockTextureData& GetBlockByType(BlockType type);

private:
	float GetTextureXOffset(int index);
	float GetTextureYOffset(int index);

public:
	inline const GLuint GetTexture() const noexcept { return mTexture; }
};

