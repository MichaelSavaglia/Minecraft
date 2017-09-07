#include "ChunkManager.h"
#include "Chunk.h"
#include <glfw3.h>
#include "Shaders\ShaderLoader.h"
#include "Camera.h"


ChunkManager::ChunkManager()
{
}


ChunkManager::~ChunkManager()
{
}

void ChunkManager::Init(glm::vec2 playerPos)
{
	
	for (int x = (playerPos.x - 10); x < (playerPos.x + 10); ++x)
	{
		for (int z = (playerPos.y - 10); z < (playerPos.y + 10); ++z)
		{
			Chunk* chunk = new Chunk(x, z);
			mChunks.push_back(chunk);
		}
	}

	/* THIS CODE WILL BE MOVED INTO RENDERER INIT*/
	glGenBuffers(1, &posBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, posBuffer);
	glBufferData(GL_ARRAY_BUFFER, (4096 * 3) * sizeof(GLint), NULL, GL_STATIC_DRAW);

	glGenBuffers(1, &textureoffsetBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, textureoffsetBuffer);
	glBufferData(GL_ARRAY_BUFFER, (4096 * 3) * sizeof(GLfloat), NULL, GL_STATIC_DRAW);

	glGenBuffers(1, &cubeBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, cubeBuffer);
	glBufferData(GL_ARRAY_BUFFER, CubeData::mVertices.size() * sizeof(GLfloat), &CubeData::mVertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &textureBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	glBufferData(GL_ARRAY_BUFFER, CubeData::mUVs.size() * sizeof(GLfloat), &CubeData::mUVs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, CubeData::mNormals.size() * sizeof(GLfloat), &CubeData::mNormals[0], GL_STATIC_DRAW);

	ProgramID = ShaderUtil::LoadShaders("Shaders/VertexShader.glsl", "Shaders/FragmentShader.glsl");



	MatrixID = glGetUniformLocation(ProgramID, "MVP");
	ModelID = glGetUniformLocation(ProgramID, "Model");
	ViewID = glGetUniformLocation(ProgramID, "View");
	DiffuseID = glGetUniformLocation(ProgramID, "material.diffuse");
	SpecularID = glGetUniformLocation(ProgramID, "materlal.specular");

	TextureSampler = glGetUniformLocation(ProgramID, "myTextureSampler");
}

void ChunkManager::Render(Camera* cam, TextureAtlas* textureAtlas)
{
	glm::mat4 Model = glm::mat4(1.0f);
	auto projection = cam->GetProjectionMatrix();
	auto view = cam->GetViewMatrix();
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glClearColor(0.529, 0.807, 0.980, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(ProgramID);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureAtlas->GetTexture());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glUniform1i(TextureSampler, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, cubeBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	for (size_t i = 0; i < mChunks.size(); ++i)
	{


		glEnableVertexAttribArray(1);
		glBufferStorage(GL_ARRAY_BUFFER, mChunks.at(i)->GetChunkCubePosList().size() * sizeof(GLint), &mChunks.at(i)->GetChunkCubePosList()[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, posBuffer);
		glVertexAttribIPointer(1, 3, GL_INT, 0, (void*)0);



		glEnableVertexAttribArray(4);
		glBufferStorage(GL_ARRAY_BUFFER, mChunks.at(i)->GetTextureData().size() * sizeof(GLint), &mChunks.at(i)->GetTextureData()[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, textureoffsetBuffer);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glm::mat4 mvp = projection * view * Model;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

		auto camPos = cam->GetPos();
		glUniform3f(glGetUniformLocation(ProgramID, "eye"), camPos.x, camPos.y, camPos.z);

		glUniform3f(glGetUniformLocation(ProgramID, "light.direction"), 0.1f, -1.0f, 0.2f);
		glUniform3f(glGetUniformLocation(ProgramID, "light.ambient"), 0.15f, 0.15f, 0.15f);
		glUniform3f(glGetUniformLocation(ProgramID, "light.diffuse"), 0.5f, 0.5f, 0.5f);
		glUniform3f(glGetUniformLocation(ProgramID, "light.specular"), 0.2f, 0.2f, 0.2f);

		glUniform3f(glGetUniformLocation(ProgramID, "material.diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(ProgramID, "material.specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(ProgramID, "material.shininess"), 5.0f);

		glUniformMatrix4fv(ModelID, 1, GL_FALSE, &Model[0][0]);
		glUniformMatrix4fv(ViewID, 1, GL_FALSE, &view[0][0]);

		glVertexAttribDivisor(1, 1);
		glVertexAttribDivisor(4, 1);

		glDrawArraysInstanced(GL_TRIANGLES, 0, CubeData::mVertices.size(), mChunks.at(i)->GetChunkCubePosList().size() / 3);
		glVertexAttribDivisor(1, 0);
		glVertexAttribDivisor(4, 0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(4);
	}
	glDisableVertexAttribArray(0);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);





	//button->Update();
	glDisable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
