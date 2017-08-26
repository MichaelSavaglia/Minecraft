#pragma once
#include "CubeData.h"
#include <vector>
#include <vec3.hpp>
class Section
{
public:
	Section(Types::uint8 yPos);
	~Section();

	std::vector<GLfloat> GenPosData();
	inline Types::uint8 GetYPos() {return mYPos;}

private:
	CubeData::CubeType mBlockIDs[4096];

	unsigned short mYPos;
};

