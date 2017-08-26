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
		vec2 vertexTopLeft = vec2(x + i*size, y + size);
		vec2 vertexTopRight = vec2(x + i*size + size, y + size);
		vec2 vertexBotRight = vec2(x + i*size + size, y);
		vec2 vertexBotLeft = vec2(x + i*size, y);

		vertices.push_back(vertexTopLeft);
		vertices.push_back(vertexBotLeft);
		vertices.push_back(vertexTopRight);

		vertices.push_back(vertexBotRight);
		vertices.push_back(vertexTopRight);
		vertices.push_back(vertexBotLeft);

		char character = text[i];
		float uv_x = (character % 16) / 16.0f;
		float uv_y = (character / 16) / 16.0f;

		vec2 uvTopLeft = vec2(uv_x, 1.0f - uv_y);
		vec2 uvTopRight = vec2(uv_x + 1.0f / 16.0f, 1.0f - uv_y);
		vec2 uvBotRight = vec2(uv_x + 1.0f / 16.0f, 1.0f - (uv_y + 1.0f / 16.0f));
		vec2 uvBotLeft = vec2(uv_x, 1.0f - (uv_y + 1.0f / 16.0f));

		UVs.push_back(uvTopLeft);
		UVs.push_back(uvBotLeft);
		UVs.push_back(uvTopRight);

		UVs.push_back(uvBotRight);
		UVs.push_back(uvTopRight);
		UVs.push_back(uvBotLeft);
	}

	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec2), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mUVBuffer);
	glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(vec2), &UVs[0], GL_STATIC_DRAW);

	glUseProgram(mShader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTexture);
	glUniform1i(mUniformLocation, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, mUVBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glDisable(GL_BLEND);

	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
}