#pragma once
#include <vector>
#include <glew.h>


struct CubeData
{
	static const std::vector<GLfloat>			mVertices;
	static const std::vector<GLfloat>			mColors;
	static const std::vector<unsigned short>	mIndices;

	const enum class CubeType : uint8_t
	{
		DIRT = 0,
		AIR,
		STONE
	};
};
