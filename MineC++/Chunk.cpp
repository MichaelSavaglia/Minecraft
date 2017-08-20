#include "Chunk.h"
#include "CubeData.h"
#include "Cube.h"


Chunk::Chunk()
{
}


Chunk::~Chunk()
{
}

void Chunk::GenerateCubeData()
{
	mCubeData.resize(16);
	for (size_t i = 0; i < 16; ++i)
	{
		mCubeData.at(i).resize(16);

		for (size_t j = 0; j < 16; ++j)
		{
			mCubeData.at(i).at(j).resize(64);
		}
	}
	for (size_t x = 0; x < 16; ++x)
	{
		for (size_t z = 0; z < 16; ++z)
		{
			for (size_t y = 0; y < 64; ++y)
			{
				if (x == 0 || y == 0 || z == 0 || x == 15 || y == 63 || z == 15)
					mCubeData[x][z][y] = new Cube(CubeData::CubeType::AIR);
				else
					mCubeData[x][z][y] = new Cube(CubeData::CubeType::DIRT);
			}
		}
	}
	for (size_t x = 1; x < 16 - 1; ++x)
	{
		for (size_t z = 1; z < 16 - 1; ++z)
		{
			for (size_t y = 1; y < 64 - 1; ++y)
			{
				if (mCubeData[x][z][y + 1]->GetType() == CubeData::CubeType::AIR ||
					mCubeData[x][z][y - 1]->GetType() == CubeData::CubeType::AIR ||
					mCubeData[x][z + 1][y]->GetType() == CubeData::CubeType::AIR ||
					mCubeData[x][z - 1][y]->GetType() == CubeData::CubeType::AIR ||
					mCubeData[x + 1][z][y]->GetType() == CubeData::CubeType::AIR ||
					mCubeData[x - 1][z][y]->GetType() == CubeData::CubeType::AIR)				
				{
					mToDraw.push_back(glm::vec3(x, y, z));
					mCubeData[x][z][y]->mShouldDraw = true;
				}
				else
				{
					mCubeData[x][z][y]->mShouldDraw = false;
					int i = 0;
				}
			}
		}
	}
	int i = 0;
}