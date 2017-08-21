#pragma once
#include <ios>
#include <vector>
#include <glm.hpp>

#include <glew.h>

class Cube;

class Chunk
{
public:
	Chunk();
	~Chunk();

	void GenerateCubeData();
	inline std::vector<std::vector<std::vector<Cube*>>> GetCubeData() const { return mCubeData; }
	std::vector<GLfloat> mChunkMesh;
	std::vector<GLfloat> mChunkColours;
	std::vector<unsigned short> mChunkIndices;
private:
	std::vector<std::vector<std::vector<Cube*>>> mCubeData;
};

