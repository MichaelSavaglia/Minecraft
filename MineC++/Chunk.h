#pragma once
#include <ios>
#include <vector>
#include <glm.hpp>
class Cube;

class Chunk
{
public:
	Chunk();
	~Chunk();

	void GenerateCubeData();
	inline std::vector<std::vector<std::vector<Cube*>>> GetCubeData() const { return mCubeData; }
	std::vector<glm::vec3> mToDraw;
private:
	std::vector<std::vector<std::vector<Cube*>>> mCubeData;
};

