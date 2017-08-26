#pragma once
#include "CubeData.h"
#include <vector>
#include <vec3.hpp>
class Section
{
public:
	Section(uint8 yPos);
	~Section();

	void GenPosList(int x, int z);

	inline uint8 GetYPos()		const {return mYPos;}

	inline std::vector<GLfloat> const GetPosList() { return mPosList; }

private:
	CubeData::CubeType mBlockIDs[4096];
	std::vector<GLfloat> mPosList;
	unsigned short mYPos;
};

