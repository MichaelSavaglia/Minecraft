#pragma once
#include <glew.h>
#include <vector>
#include <glm.hpp>

class iUIElement
{
public:
	iUIElement(int x, int y, int width, int height);
	virtual ~iUIElement();
	virtual void Draw() = 0;
	virtual void SetBuffers();
	inline GLuint GetTextureID() { return mTexture; };
	inline void ChangeSize(int width, int height) { mWidth = width; mHeight = height; mBufferNeedsUpdate = true; };
	inline void ChangePosition(int x, int y) { mX = x; mY = y; mBufferNeedsUpdate = true; };
	int GetWindowHeight();
	inline void SetAllignment(int8_t anchor) { mAnchor = anchor; };

	inline int GetX() { return mX; }
	inline int GetY() { return mY; }
	inline int GetWidth() { return mWidth; }
	inline int GetHeight() { return mHeight; }

private:
	void SetVerts(glm::vec2& top_left, glm::vec2& top_right, glm::vec2& bot_left, glm::vec2& bot_right);

protected:
	GLuint mVertexBuffer;
	GLuint mUVBuffer;
	GLuint mTexture;

	int mX, mY;
	int mWidth, mHeight;
	bool mBufferNeedsUpdate;

	std::vector<glm::vec2> vertices;
	std::vector<glm::vec2> UVs;

	int8_t mAnchor;
};

class UIAllignment
{
public:
	static const int8_t TOP_LEFT	= 0b00000001;
	static const int8_t TOP_MIDDLE	= 0b00000010;
	static const int8_t TOP_RIGHT	= 0b00000100;
	static const int8_t BOT_LEFT	= 0b00001000;
	static const int8_t BOT_MIDDLE	= 0b00010000;
	static const int8_t BOT_RIGHT	= 0b00100000;
	static const int8_t CENTER		= 0b01000000;

private:
	static const int8_t UNUSED		= 0b10000000;
};