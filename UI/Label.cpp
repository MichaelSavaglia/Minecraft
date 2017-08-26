#include "Label.h"
#include <glew.h>
#include <SOIL.h>
#include <glm.hpp>
#include <vector>


Label::Label(char* text, int x, int y, int size)
{
	mText = text;
	mX = x;
	mY = y;
	mSize = size;

	mTexture = SOIL_load_OGL_texture(
		"Textures/Fonts/Arial56(64x64).png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
	);

	glGenBuffers(1, &mVertexBuffer);
	glGenBuffers(1, &mUVBuffer);

	SetBuffers();
}


Label::~Label()
{
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mUVBuffer);
	glDeleteTextures(1, &mTexture); //TO GO WHEN TEXTURES ARE MANAGED
}

void Label::Draw()
{
	iUIElement::Draw();
}

void Label::SetBuffers()
{
	vertices.clear();
	UVs.clear();

	using glm::vec2;

	GLuint length = mText.length();

	for (unsigned int i = 0; i < length; ++i)
	{
		vec2 vertexTopLeft = vec2(mX + i*mSize, mY + mSize);
		vec2 vertexTopRight = vec2(mX + i*mSize + mSize, mY + mSize);
		vec2 vertexBotRight = vec2(mX + i*mSize + mSize, mY);
		vec2 vertexBotLeft = vec2(mX + i*mSize, mY);

		vertices.push_back(vertexTopLeft);
		vertices.push_back(vertexBotLeft);
		vertices.push_back(vertexTopRight);

		vertices.push_back(vertexBotRight);
		vertices.push_back(vertexTopRight);
		vertices.push_back(vertexBotLeft);

		char character = mText[i];
		float uv_x = (character % 16) / 16.0f;
		float uv_y = (character >> 4) / 16.0f;

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
}
