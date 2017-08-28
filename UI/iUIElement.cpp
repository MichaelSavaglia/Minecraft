#include "iUIElement.h"
#include <glfw3.h>

iUIElement::iUIElement(int x, int y, int width, int height)
{
	mAnchor = UIAllignment::CENTER;

	glCreateBuffers(1, &mVertexBuffer);
	glCreateBuffers(1, &mUVBuffer);

	mX = x;
	mY = y;
	mWidth = width;
	mHeight = height;

	mBufferNeedsUpdate = true;
}

void iUIElement::SetBuffers()
{
	using glm::vec2;
	vec2 vertexTopLeft;
	vec2 vertexTopRight;
	vec2 vertexBotRight;
	vec2 vertexBotLeft;

	SetVerts(vertexTopLeft, vertexTopRight, vertexBotLeft, vertexBotRight);

	vertices.push_back(vertexTopLeft);
	vertices.push_back(vertexBotLeft);
	vertices.push_back(vertexTopRight);

	vertices.push_back(vertexBotRight);
	vertices.push_back(vertexTopRight);
	vertices.push_back(vertexBotLeft);

	vec2 uvTopLeft = vec2(0.0f, 1.0f);
	vec2 uvTopRight = vec2(1.0f, 1.0f);
	vec2 uvBotRight = vec2(1.0f, 0.0f);
	vec2 uvBotLeft = vec2(0.0f, 0.0f);

	UVs.push_back(uvTopLeft);
	UVs.push_back(uvBotLeft);
	UVs.push_back(uvTopRight);

	UVs.push_back(uvBotRight);
	UVs.push_back(uvTopRight);
	UVs.push_back(uvBotLeft);
}


iUIElement::~iUIElement()
{
}

void iUIElement::Draw()
{
	//if (mBufferNeedsUpdate)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
		glNamedBufferStorage(mVertexBuffer, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_DYNAMIC_STORAGE_BIT);
		glBindBuffer(GL_ARRAY_BUFFER, mUVBuffer);
		glNamedBufferStorage(mUVBuffer, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_DYNAMIC_STORAGE_BIT);
		//mBufferNeedsUpdate = false;
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTexture);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, mUVBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glDisable(GL_BLEND);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

int iUIElement::GetWindowHeight()
{
	return 0;
}

void iUIElement::SetVerts(glm::vec2 & top_left, glm::vec2 & top_right, glm::vec2 & bot_left, glm::vec2 & bot_right)
{
	using glm::vec2;

	//Yeah... I know
	if (mAnchor & UIAllignment::TOP_LEFT)
	{
		top_left	= vec2(mX					, mY);
		top_right	= vec2(mX + 2.0f * mWidth	, mY);
		bot_left	= vec2(mX					, mY - 2.0f * mHeight);
		bot_right	= vec2(mX + 2.0f * mWidth	, mY - 2.0f * mHeight);
	}
	else if (mAnchor & UIAllignment::TOP_MIDDLE)
	{
		top_left	= vec2(mX - 1.0f * mWidth	, mY);
		top_right	= vec2(mX + 1.0f * mWidth	, mY);
		bot_left	= vec2(mX + 1.0f * mWidth	, mY - 2.0f * mHeight);
		bot_right	= vec2(mX - 1.0f * mWidth	, mY - 2.0f * mHeight);
	}
	else if (mAnchor & UIAllignment::TOP_RIGHT)
	{
		top_left	= vec2(mX - 2.0f * mWidth	, mY);
		top_right	= vec2(mX					, mY);
		bot_left	= vec2(mX - 2.0f * mWidth	, mY - 2.0f * mHeight);
		bot_right	= vec2(mX					, mY - 2.0f * mHeight);
	}
	else if (mAnchor & UIAllignment::BOT_RIGHT)
	{
		top_left	= vec2(mX - 2.0f * mWidth	, mY + 2.0f * mHeight);
		top_right	= vec2(mX					, mY + 2.0f * mHeight);
		bot_left	= vec2(mX - 2.0f * mWidth	, mY);
		bot_right	= vec2(mX					, mY);
	}
	else if (mAnchor & UIAllignment::BOT_MIDDLE)
	{
		top_left	= vec2(mX - 1.0f * mWidth	, mY + 2.0f * mHeight);
		top_right	= vec2(mX + 1.0f * mWidth	, mY + 2.0f * mHeight);
		bot_left	= vec2(mX + 1.0f * mWidth	, mY);
		bot_right	= vec2(mX - 1.0f * mWidth	, mY);
	}
	else if (mAnchor & UIAllignment::BOT_LEFT)
	{
		top_left	= vec2(mX					, mY + 2.0f * mHeight);
		top_right	= vec2(mX + 2.0f * mWidth	, mY + 2.0f * mHeight);
		bot_left	= vec2(mX					, mY);
		bot_right	= vec2(mX + 2.0f * mWidth	, mY);
	}
	else //if (mAnchor & UIAllignment::CENTER) //DEFAULT ALLIGNMENT
	{
		top_left = vec2(mX - 1.0f * mWidth, mY + 1.0f * mHeight);
		top_right = vec2(mX + 1.0f * mWidth, mY + 1.0f * mHeight);
		bot_left = vec2(mX - 1.0f * mWidth, mY - 1.0f * mHeight);
		bot_right = vec2(mX + 1.0f * mWidth, mY - 1.0f * mHeight);
	}
}
