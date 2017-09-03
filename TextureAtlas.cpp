#include <glew.h>
#include <glfw3.h>
#include <math.h>
#include "TextureAtlas.h"
#include "TextureManager.h"
#include "Types.h"


TextureAtlas::TextureAtlas(std::string path, uint8 rowSize) : mRowCount(rowSize), mPath(path)
{
	mTexture = TextureManager::Instance()->LoadTexture(path.c_str());

	mBlockData[BlockType::DEFAULT]		= BlockTextureData((float)rowSize, GetTextureXOffset(0), GetTextureYOffset(0));
	mBlockData[BlockType::DIRT]			= BlockTextureData((float)rowSize, GetTextureXOffset(3), GetTextureYOffset(3));
	mBlockData[BlockType::GRASS]		= BlockTextureData((float)rowSize, GetTextureXOffset(6), GetTextureYOffset(6));
	mBlockData[BlockType::STONE]		= BlockTextureData((float)rowSize, GetTextureXOffset(9), GetTextureYOffset(9));
	mBlockData[BlockType::WOOD]			= BlockTextureData((float)rowSize, GetTextureXOffset(12), GetTextureYOffset(12));
	mBlockData[BlockType::SAND]			= BlockTextureData((float)rowSize, GetTextureXOffset(15), GetTextureYOffset(15));
	mBlockData[BlockType::COBBLESTONE]	= BlockTextureData((float)rowSize, GetTextureXOffset(18), GetTextureYOffset(18));

}

TextureAtlas::~TextureAtlas()
{
	
}

BlockTextureData TextureAtlas::GetBlockByType(BlockType type)
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

void TextureAtlas::ReloadTextureAtlas()
{
	mTexture = TextureManager::Instance()->ReloadTexture(mTexture,mPath.c_str());
}
