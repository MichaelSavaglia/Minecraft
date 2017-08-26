#include "Canvas.h"
#include "Shaders\ShaderLoader.h"
#include <glm.hpp>
#include <SOIL.h>
#include <iostream>
#include <glfw3.h>

Canvas::Canvas()
{
	/*mTexture = SOIL_load_OGL_texture(
		"Textures/Fonts/Arial56(64x64).png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);*/

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	mTexture = SOIL_load_OGL_texture(
		"Textures/Fonts/Arial56(64x64).png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
	);

	glGenBuffers(1, &mVertexBuffer);
	glGenBuffers(1, &mUVBuffer);

	mShader = ShaderUtil::LoadShaders("Shaders/UIVertexShader.glsl", "Shaders/UIFragmentShader.glsl");
	glUseProgram(mShader);
	mUniformLocation = glGetUniformLocation(mShader, "myTextureSampler");

	int i = 0;
}

Canvas::~Canvas()
{
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mUVBuffer);
	glDeleteTextures(1, &mTexture);
	glDeleteProgram(mShader);
}

void Canvas::Draw(const char* text, int x, int y, int size)
{
	using namespace glm;

	GLuint length = strlen(text);

	std::vector<vec2> vertices;
	std::vector<vec2> UVs;

	for (unsigned int i = 0; i < length; ++i)
	{
		vec2 vertexTopLeft	= vec2(x + i*size		, y + size);
		vec2 vertexTopRight = vec2(x + i*size+size	, y + size);
		vec2 vertexBotRight	= vec2(x + i*size+size	, y);
		vec2 vertexBotLeft	= vec2(x + i*size		, y);

		vertices.push_back(vertexTopLeft);
		vertices.push_back(vertexBotLeft);
		vertices.push_back(vertexTopRight);

		vertices.push_back(vertexBotRight);
		vertices.push_back(vertexTopRight);
		vertices.push_back(vertexBotLeft);

		char character = text[i];
		float uv_x = (character % 16) / 16.0f;
		float uv_y = (character / 16) / 16.0f;
		
		vec2 uvTopLeft	= vec2(uv_x					, 1.0f - uv_y);
		vec2 uvTopRight = vec2(uv_x + 1.0f / 16.0f	, 1.0f - uv_y);
		vec2 uvBotRight = vec2(uv_x + 1.0f / 16.0f	, 1.0f - (uv_y + 1.0f / 16.0f));
		vec2 uvBotLeft	= vec2(uv_x					, 1.0f - (uv_y + 1.0f / 16.0f));
			
		UVs.push_back(uvTopLeft);
		UVs.push_back(uvBotLeft);
		UVs.push_back(uvTopRight);

		UVs.push_back(uvBotRight);
		UVs.push_back(uvTopRight);
		UVs.push_back(uvBotLeft);
	}

	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec2), &vertices[0]	, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mUVBuffer);
	glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(vec2)		, &UVs[0]		, GL_STATIC_DRAW);

	glUseProgram(mShader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTexture);
	glUniform1i(mUniformLocation, 0);

	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, mUVBuffer);
	glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glDisable(GL_BLEND);

	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
}

void Canvas::printText2D(const char * text, int x, int y, int size) {

	unsigned int length = strlen(text);

	// Fill buffers
	std::vector<glm::vec2> vertices;
	std::vector<glm::vec2> UVs;

	glm::vec2 vertex_up_left = glm::vec2(x - 600.0f, y + 300.0f);
	glm::vec2 vertex_up_right = glm::vec2(x + 600.0f, y + 300.0f);
	glm::vec2 vertex_down_right = glm::vec2(x + 600.0f, y - 300.0f);
	glm::vec2 vertex_down_left = glm::vec2(x - 600.0f, y - 300.0f);

	vertices.push_back(vertex_up_left);
	vertices.push_back(vertex_down_left);
	vertices.push_back(vertex_up_right);

	vertices.push_back(vertex_down_right);
	vertices.push_back(vertex_up_right);
	vertices.push_back(vertex_down_left);

	glm::vec2 uv_up_left = glm::vec2(0.0f, 1.0f);
	glm::vec2 uv_up_right = glm::vec2(1.0f, 1.0f);
	glm::vec2 uv_down_right = glm::vec2(1.0f, 0.0f);
	glm::vec2 uv_down_left = glm::vec2(0.0f, 0.0f);

	UVs.push_back(uv_up_left);
	UVs.push_back(uv_down_left);
	UVs.push_back(uv_up_right);

	UVs.push_back(uv_down_right);
	UVs.push_back(uv_up_right);
	UVs.push_back(uv_down_left);

	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mUVBuffer);
	glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_STATIC_DRAW);

	// Bind shader
	glUseProgram(mShader);

	// Bind texture
	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTexture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(mUniformLocation, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, mUVBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Draw call
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

}