#pragma once
#include <ios>
#include <vector>
class Cube; //?

class Chunk
{
public:
	Chunk();
	~Chunk();

	std::vector<std::vector<std::vector<uint8_t*>>> mCubeData;
private:
};

