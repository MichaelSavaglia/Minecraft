#pragma once


#include "glm.hpp"
#include <vector>

class Chunk;
class Camera;
class TextureAtlas;
typedef unsigned int GLuint;

class ChunkManager
{
public:
	ChunkManager();
	~ChunkManager();

	void Init(glm::vec2 playerPos);

	void Render(Camera* cam, TextureAtlas* textureAtlas);

private:
	std::vector<Chunk*> mChunks;

	/* TEMP */
	GLuint posBuffer;
	GLuint textureoffsetBuffer;
	GLuint cubeBuffer;
	GLuint textureBuffer;
	GLuint normalBuffer;

	GLuint ProgramID;

	GLuint MatrixID;
	GLuint ModelID;
	GLuint ViewID;
	GLuint DiffuseID;
	GLuint SpecularID;
	GLuint TextureSampler;
};

