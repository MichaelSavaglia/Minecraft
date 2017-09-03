#include <glew.h>
#include <glfw3.h>
#include <math.h>
#include "TextureAtlas.h"
#include "TextureManager.h"
#include "Types.h"


TextureAtlas::TextureAtlas(std::string path, uint8 rowSize) : mRowCount(rowSize)
{
	mTexture = TextureManager::Instance()->LoadTexture(path.c_str());

	mBlockData[BlockType::DEFAULT]	= BlockTextureData((float)rowSize, GetTextureXOffset(0), GetTextureYOffset(0));
	mBlockData[BlockType::DIRT]		= BlockTextureData((float)rowSize, GetTextureXOffset(1), GetTextureYOffset(1));
	mBlockData[BlockType::GRASS]	= BlockTextureData((float)rowSize, GetTextureXOffset(2), GetTextureYOffset(2));
	mBlockData[BlockType::STONE]	= BlockTextureData((float)rowSize, GetTextureXOffset(3), GetTextureYOffset(3));
}


TextureAtlas::~TextureAtlas()
{
	
}

const BlockTextureData & TextureAtlas::GetBlockByType(BlockType type)
{
	auto isPresentInChace = mBlockData.count(type);

	if (!isPresentInChace) return mBlockData[BlockType::DEFAULT];

	return  mBlockData[type];

}

float TextureAtlas::GetTextureXOffset(int index)
{
	int columnNumber = index % mRowCount;
	return (float)columnNumber / (float)mRowCount;
}

float TextureAtlas::GetTextureYOffset(int index)
{
	int rowNumber = floorf(index/mRowCount);
	return (float)rowNumber / (float)mRowCount;
}
