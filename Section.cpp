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

std::vector<GLfloat> Section::GenPosData()
{
	std::vector<GLfloat> out;
	out.reserve(4096 * 3);
	for (size_t i = 0; i < 4096; ++i)
	{
		out.push_back(i & 0xF);
		out.push_back((i >> 4) & 0xF);
		out.push_back((i >> 8) & 0xF );
	}
	return out;
}
