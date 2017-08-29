#include "Label.h"
#include <glew.h>
#include <SOIL.h>
#include <glm.hpp>
#include <vector>



Label::Label(char* text, int x, int y, int size) : iUIElement(x, y, size, size)
{
	mText = text;
	mAllignment = TEXT_ALLIGNMENT::LEFT;

	mTexture = SOIL_load_OGL_texture(
		"Textures/Fonts/Consolas128(2048x2048).tga",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
	);
}

Label::Label(std::string text, int x, int y, int size) : iUIElement(x, y, size, size)
{
	mText = text;
	mAllignment = TEXT_ALLIGNMENT::LEFT;

	mTexture = SOIL_load_OGL_texture(
		"Textures/Fonts/Consolas128(2048x2048).tga",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
	);
}


Label::~Label()
{
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mUVBuffer);
	glDeleteTextures(1, &mTexture); //TO GO WHEN TEXTURES ARE MANAGED
}

void Label::Draw()
{
	if (mBufferNeedsUpdate)
	{
		SetBuffers();
		mBufferNeedsUpdate = false;
	}

	iUIElement::Draw();
}

void Label::SetBuffers()
{
	vertices.clear();
	UVs.clear();

	using glm::vec2;

	GLuint length = mText.length();

	vec2 vertexTopLeft;
	vec2 vertexTopRight;
	vec2 vertexBotRight;
	vec2 vertexBotLeft;

	vec2 uvTopLeft;
	vec2 uvTopRight;
	vec2 uvBotRight;
	vec2 uvBotLeft;

	float halfHeight = mHeight / 2.0f;

	switch (mAllignment)
	{
	case TEXT_ALLIGNMENT::LEFT:
		for (unsigned int i = 0; i < length; ++i)
		{
			vertexTopLeft = vec2(mX + i*mHeight, mY + halfHeight);
			vertexTopRight = vec2(mX + i*mHeight + mHeight, mY + halfHeight);
			vertexBotRight = vec2(mX + i*mHeight + mHeight, mY - halfHeight);
			vertexBotLeft = vec2(mX + i*mHeight, mY - halfHeight);

			vertices.push_back(vertexTopLeft);
			vertices.push_back(vertexBotLeft);
			vertices.push_back(vertexTopRight);

			vertices.push_back(vertexBotRight);
			vertices.push_back(vertexTopRight);
			vertices.push_back(vertexBotLeft);

			char character = mText[i];
			float uv_x = (character & 0xF) / 16.0f;
			float uv_y = (character >> 4) / 16.0f;

			uvTopLeft = vec2(uv_x, 1.0f - uv_y);
			uvTopRight = vec2(uv_x + 1.0f / 16.0f, 1.0f - uv_y);
			uvBotRight = vec2(uv_x + 1.0f / 16.0f, 1.0f - (uv_y + 1.0f / 16.0f));
			uvBotLeft = vec2(uv_x, 1.0f - (uv_y + 1.0f / 16.0f));

			UVs.push_back(uvTopLeft);
			UVs.push_back(uvBotLeft);
			UVs.push_back(uvTopRight);

			UVs.push_back(uvBotRight);
			UVs.push_back(uvTopRight);
			UVs.push_back(uvBotLeft);
		}
		break;
	}
	
}
