#pragma once
#include "CubeData.h"
#include <vector>
#include <vec3.hpp>
#include "BlockTypeEnum.h"
#include "TextureAtlas.h"
class Section
{
public:
	Section(uint8 yPos);
	~Section();

	void GenPosList(int x, int z, int heightMap[16][16]);

	inline uint8 GetYPos()		const {return mYPos;}

	inline std::vector<GLint> const GetPosList() { return mPosList; }
	inline std::vector<GLfloat> const GetTextureData() { return mTextureData; }

private:
	BlockType mBlockIDs[4096];
	std::vector<GLint> mPosList;
	std::vector<GLfloat> mTextureData;
	TextureAtlas* mTextureAtlas;
	unsigned short mYPos;
};

