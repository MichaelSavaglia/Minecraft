#include "chunk.h"
#include "HeightGenerator.h"

Chunk::Chunk(int xPos, int zPos) : mXPos(xPos), mZPos(zPos)
{
	GenerateHeightMap();
	GenerateSections();
	GeneratePosList();
}

Chunk::~Chunk()
{
	delete[] mSections;
}

void Chunk::Draw()
{
}

void Chunk::GenerateSections()
{
	for (size_t i = 0; i < 16; ++i)
	{
		mSections[i] = new Section(i);
		mSections[i]->GenPosList(mXPos, mZPos, mHeightMap);
	}
}

void Chunk::GeneratePosList()
{
	mPosList.reserve(4096 * 3 * 16); // Reserve enough memory to hold every voxel pos
	for (size_t i = 0; i < 16; ++i)
	{
		auto list = mSections[i]->GetPosList();
		mPosList.insert(mPosList.end(), list.begin(), list.end());
	}
	mPosList.shrink_to_fit(); // Remove any excess memory
}

void Chunk::GenerateHeightMap()
{
	HeightGenerator* gen = new HeightGenerator(10000);
	for (size_t x = 0; x < 16; ++x)
	{
		for (size_t z = 0; z < 16; ++z)
		{
			mHeightMap[x][z] = gen->GenerateHeight(x, z);
		}
	}
}
