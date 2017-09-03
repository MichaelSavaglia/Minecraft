#include "Section.h"
#include <glfw3.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "BlockTypeEnum.h"


Section::Section(uint8 yPos) : mYPos(yPos)
{

	mTextureAtlas = new TextureAtlas("Textures/TextureAtlas.png", 6);

	for (size_t i = 0; i < 4096; ++i)
	{
		mBlockIDs[i] = BlockType::DIRT;
	}
}


Section::~Section()
{
}

void Section::GenPosList(int x, int z, int heightMap[16][16])
{
	mPosList.reserve(4096 * 3);
	for (size_t i = 0; i < 4096; ++i)
	{
		int localX = (i & 0xF);
		int xPos = localX + (x << 4);
		int localY = ((i >> 4) & 0xF);
		int yPos = localY + (mYPos << 4);
		int localZ = ((i >> 8) & 0xF);
		int zPos = localZ + (z << 4);
		int maxY = heightMap[localX][localZ];
		if (yPos <= maxY && yPos >= maxY - 8)
		{
			mPosList.push_back(xPos);
			mPosList.push_back(yPos);
			mPosList.push_back(zPos);

			if (yPos <= maxY && yPos >= maxY-1)
			{
				auto blockType = mTextureAtlas->GetBlockByType(BlockType::GRASS);
				mTextureData.push_back(blockType.x);
				mTextureData.push_back(blockType.y);
				mTextureData.push_back(blockType.z);
			}
			else if (yPos <= maxY-1 && yPos >= maxY - 3)
			{
				auto blockType = mTextureAtlas->GetBlockByType(BlockType::DIRT);
				mTextureData.push_back(blockType.x);
				mTextureData.push_back(blockType.y);
				mTextureData.push_back(blockType.z);
			}
			else if(yPos <= maxY - 3 && yPos >= maxY - 8)
			{
				auto blockType = mTextureAtlas->GetBlockByType(BlockType::STONE);
				mTextureData.push_back(blockType.x);
				mTextureData.push_back(blockType.y);
				mTextureData.push_back(blockType.z);
			}
		}
	}
	mPosList.shrink_to_fit();
}
