#include "Chunk.h"
#include "CubeData.h"
#include "Cube.h"

#include <gtc/matrix_transform.hpp>
#include <gtx\transform.hpp>
#include <glfw3.h>
#include <iostream>

Chunk::Chunk()
{
}


Chunk::~Chunk()
{
}

void Chunk::GenerateCubeData()
{
	auto xMax = 16;
	auto zMax = 16;
	auto yMax = 64;
	auto xMaxIndex = xMax - 1;
	auto zMaxIndex = zMax - 1;
	auto yMaxIndex = yMax - 1;

	mCubeData.resize(xMax);
	for (size_t i = 0; i < xMax; ++i)
	{
		mCubeData.at(i).resize(zMax);

		for (size_t j = 0; j < zMax; ++j)
		{
			mCubeData.at(i).at(j).resize(yMax);
		}
	}
	for (size_t x = 0; x < xMax; ++x)
	{
		for (size_t z = 0; z < zMax; ++z)
		{
			for (size_t y = 0; y < yMax; ++y)
			{
				if (x == 0 || y == 0 || z == 0 || x == xMaxIndex || y == yMaxIndex || z == zMaxIndex)
					mCubeData[x][z][y] = new Cube(CubeData::CubeType::AIR);
				else
					mCubeData[x][z][y] = new Cube((y & 1) ? CubeData::CubeType::DIRT : CubeData::CubeType::STONE);
			}
		}
	}
	int count = 0;
	auto start = glfwGetTime();
	int type = 0;
	glm::vec2 uvMod = glm::vec2();
	for (size_t x = 0; x < xMax; ++x)
	{
		for (size_t z = 0; z < zMax; ++z)
		{
			for (size_t y = 0; y < yMax; ++y)
			{
				if ((y != yMaxIndex	&& mCubeData[x][z][y + 1]->GetType() == CubeData::CubeType::AIR) ||
					(y != 0			&& mCubeData[x][z][y - 1]->GetType() == CubeData::CubeType::AIR) ||
					(z != zMaxIndex	&& mCubeData[x][z + 1][y]->GetType() == CubeData::CubeType::AIR) ||
					(z != 0			&& mCubeData[x][z - 1][y]->GetType() == CubeData::CubeType::AIR) ||
					(x != xMaxIndex	&& mCubeData[x + 1][z][y]->GetType() == CubeData::CubeType::AIR) ||
					(x != 0			&& mCubeData[x - 1][z][y]->GetType() == CubeData::CubeType::AIR))				
				{
					auto pos = glm::vec3(x, y, z);
					for (size_t i = 0; i < CubeData::mVertices.size(); i += 3)
					{
						mChunkMesh.push_back(CubeData::mVertices[i] + pos.x);
						mChunkMesh.push_back(CubeData::mVertices[i + 1] + pos.y);
						mChunkMesh.push_back(CubeData::mVertices[i + 2] + pos.z);
					}

					type = x;
					std::cout << "type: " << type << std::endl;
					uvMod.x = 0.1f * floor(type / 10);
					uvMod.y = 0.1f * (9 - (type % 10));
					for (size_t i = 0; i < CubeData::mUVs.size(); i += 2)
					{
						mChunkUVs.push_back(CubeData::mUVs[i] + uvMod.x);
						mChunkUVs.push_back(CubeData::mUVs[i + 1] + uvMod.y);
					}
					//for (size_t i = 0; i < CubeData::mIndices.size(); ++i)
					//{
						//mChunkIndices.push_back(CubeData::mIndices[i] + count);
					//}
					count += 8;
				}
			}
		}
	}
	auto finish = glfwGetTime();
	std::cout << finish - start << "--------------" << std::endl;
	int i = 0;
}