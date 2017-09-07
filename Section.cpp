#include "Section.h"
#include <glfw3.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "BlockTypeEnum.h"


Section::Section(uint8 yPos) : mYPos(yPos)
{

	mTextureAtlas = TextureAtlas::Instance();
	mBlockIDs = std::vector<BlockType>(4096, BlockType::AIR);
}


Section::~Section()
{
}

void Section::GenPosList(int x, int z, int heightMap[16][16])
{
	mPosList.reserve(4096 * 3);
	mTextureData.reserve(4096 * 3);
	for (size_t i = 0; i < 4096; ++i)
	{
		int localX = (i & 0xF);
		int xPos = localX + (x << 4);

		int localY = ((i >> 8) & 0xF);
		int yPos = localY + (mYPos << 4);

		int localZ = ((i >> 4) & 0xF);
		int zPos = localZ + (z << 4);

		int maxY = heightMap[localX][localZ];

		if (yPos <= maxY)
		{
			if (yPos == maxY)
			{
				mBlockIDs[i] = BlockType::GRASS;
			}
			else if (yPos < maxY && yPos >= maxY - 3)
			{
				mBlockIDs[i] = BlockType::DIRT;
			}
			else
			{
				mBlockIDs[i] = BlockType::STONE;
			}
		}
	}

	for (size_t i = 0; i < 4096; ++i)
	{
		if (mBlockIDs[i] == BlockType::AIR)
			continue;

		int localX = (i & 0xF);
		int xPos = localX + (x << 4);

		int localY = ((i >> 8) & 0xF);
		int yPos = localY + (mYPos << 4);

		int localZ = ((i >> 4) & 0xF);
		int zPos = localZ + (z << 4);

		bool isNextToAir = false;

		if (localX < 15)
		{
			int xPlusOne = localY * 16 * 16 + localZ * 16 + (localX + 1);
			if (mBlockIDs[xPlusOne] == BlockType::AIR)
			{
				mPosList.push_back(xPos);
				mPosList.push_back(yPos);
				mPosList.push_back(zPos);
				auto blockType = mTextureAtlas->GetBlockByType(mBlockIDs[i]);
				mTextureData.push_back(blockType.x);
				mTextureData.push_back(blockType.y);
				mTextureData.push_back(blockType.z);
				continue;
			}
		}

		if (localX > 0)
		{
			int xMinusOne = localY * 16 * 16 + (localZ * 16) + localX - 1;
			if (mBlockIDs[xMinusOne] == BlockType::AIR)
			{
				mPosList.push_back(xPos);
				mPosList.push_back(yPos);
				mPosList.push_back(zPos);
				auto blockType = mTextureAtlas->GetBlockByType(mBlockIDs[i]);
				mTextureData.push_back(blockType.x);
				mTextureData.push_back(blockType.y);
				mTextureData.push_back(blockType.z);
				continue;
			}
		}

		if (localY < 15)
		{
			int yPlusOne = (localY + 1) * 16 * 16 + localZ * 16 + localX;
			if (mBlockIDs[yPlusOne] == BlockType::AIR)
			{
				mPosList.push_back(xPos);
				mPosList.push_back(yPos);
				mPosList.push_back(zPos);
				auto blockType = mTextureAtlas->GetBlockByType(mBlockIDs[i]);
				mTextureData.push_back(blockType.x);
				mTextureData.push_back(blockType.y);
				mTextureData.push_back(blockType.z);
				continue;
			}
		}

		if (localY > 0)
		{
			int yMinusOne = (localY - 1) * 16 * 16 + localZ * 16 + localX;
			if (mBlockIDs[yMinusOne] == BlockType::AIR)
			{
				mPosList.push_back(xPos);
				mPosList.push_back(yPos);
				mPosList.push_back(zPos);
				auto blockType = mTextureAtlas->GetBlockByType(mBlockIDs[i]);
				mTextureData.push_back(blockType.x);
				mTextureData.push_back(blockType.y);
				mTextureData.push_back(blockType.z);
				continue;
			}
		}

		if (localZ < 15)
		{
			int zPlusOne = localY * 16 * 16 + (localZ + 1) * 16 + localX;
			if (mBlockIDs[zPlusOne] == BlockType::AIR)
			{
				mPosList.push_back(xPos);
				mPosList.push_back(yPos);
				mPosList.push_back(zPos);
				auto blockType = mTextureAtlas->GetBlockByType(mBlockIDs[i]);
				mTextureData.push_back(blockType.x);
				mTextureData.push_back(blockType.y);
				mTextureData.push_back(blockType.z);
				continue;
			}
		}

		if (localZ > 0)
		{
			int zMinusOne = localY * 16 * 16 + (localZ - 1) * 16 + localX;
			if (mBlockIDs[zMinusOne] == BlockType::AIR)
			{
				mPosList.push_back(xPos);
				mPosList.push_back(yPos);
				mPosList.push_back(zPos);
				auto blockType = mTextureAtlas->GetBlockByType(mBlockIDs[i]);
				mTextureData.push_back(blockType.x);
				mTextureData.push_back(blockType.y);
				mTextureData.push_back(blockType.z);
				continue;
			}
		}


	}
	mTextureData.shrink_to_fit();
	mPosList.shrink_to_fit();
}
