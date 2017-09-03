#pragma once
#include <vector>
#include <glew.h>
#include "Types.h"

struct CubeData
{
	static const std::vector<GLfloat>			mVertices;
	static const std::vector<GLfloat>			mNormals;
	static const std::vector<GLfloat>			mColors;
	static const std::vector<GLfloat>			mUVs;
	static const std::vector<unsigned short>	mIndices;
	 
};
