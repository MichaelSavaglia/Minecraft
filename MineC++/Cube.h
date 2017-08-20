#pragma once
#include "CubeData.h"
class Cube
{
public:
	Cube(CubeData::CubeType type);
	~Cube();

	inline CubeData::CubeType GetType() const { return mType; }
	bool mShouldDraw;
private:
	CubeData::CubeType mType;
};

