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

void Section::GenPosList(int x, int z)
{
	mPosList.reserve(4096 * 3);
	for (size_t i = 0; i < 4096; ++i)
	{
		mPosList.push_back((i & 0xF) + (x << 4));
		mPosList.push_back(((i >> 4) & 0xF) + (mYPos << 4));
		mPosList.push_back(((i >> 8) & 0xF) + (z << 4));
	}
	mPosList.shrink_to_fit();
}
