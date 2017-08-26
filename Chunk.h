#pragma once

#include "Section.h"
#include <glfw3.h>

class Chunk final
{
public:

	Chunk(int xPos, int zPos);
	~Chunk();

	inline std::vector<GLfloat> const GetChunkCubePosList() { return mPosList; }

private:

	Section* mSections[16];
	std::vector<GLfloat> mPosList;
	int mXPos;
	int mZPos;

	void GenerateSections();
	void GeneratePosList();
};
