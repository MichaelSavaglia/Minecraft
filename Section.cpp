#include "Section.h"
#include <glfw3.h>
#include <iostream>
#include <vector>
#include <algorithm>

Section::Section(uint8 yPos) : mYPos(yPos)
{
	for (size_t i = 0; i < 4096; ++i)
	{
		mBlockIDs[i] = CubeData::CubeType::DIRT;
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
		if (yPos <= maxY && yPos >= maxY - 2)
		{
			mPosList.push_back(xPos);
			mPosList.push_back(yPos);
			mPosList.push_back(zPos);
		}
	}
	mPosList.shrink_to_fit();
}
