#include "Button.h"
#include <SOIL.h>
#include "../Window.h"
#include "../Input.h"

#include "../TextureManager.h"

Button::Button(const char* texturePath, int x, int y, int width, int height, std::string text) : iUIElement(x, y, width, height)
{
	mTexture = TextureManager::Instance()->LoadTexture(texturePath);

	mLabel = new Label(text, x, y, height);
	mAnchor = UIAllignment::CENTER;
	mInput = Input::Instance();
	mShouldRelease = false;
}


Button::~Button()
{

}


void Button::Update()
{
	if (mInput->GetMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
	{
		if (!mShouldRelease)
		{
			glm::vec2 pos = mInput->GetMousePosition();
			pos.y = 720 - pos.y;

			if (pos.x < mX + mWidth && pos.x > mX - mWidth &&
				pos.y < mY + mHeight && pos.y > mY - mHeight)
			{
				std::invoke(mOnClick);
			}
		}
		mShouldRelease = true;
	}
	else
	{
		if (mShouldRelease)
		{
			glm::vec2 pos = mInput->GetMousePosition();
			pos.y = 720 - pos.y;

			if (pos.x < mX + mWidth && pos.x > mX - mWidth &&
				pos.y < mY + mHeight && pos.y > mY - mHeight)
			{
				std::invoke(mOnRelease);
			}
		}
		mShouldRelease = false;
	}

	
}

void Button::Draw()
{
	if (mBufferNeedsUpdate)
	{
		SetBuffers();
		mBufferNeedsUpdate = false;
	}
	

	//not sure if what i did was correct but you need to define background texture more clearly
	iUIElement::Draw();

	mLabel->Draw();
}

void Button::SetAllignment(int8_t anchor)
{
	iUIElement::SetAllignment(anchor);

	if (mAnchor & UIAllignment::TOP_LEFT)
	{

	}
	else if (mAnchor & UIAllignment::TOP_MIDDLE)
	{

	}
	else if (mAnchor & UIAllignment::TOP_RIGHT)
	{

	}
	else if (mAnchor & UIAllignment::BOT_RIGHT)
	{

	}
	else if (mAnchor & UIAllignment::BOT_MIDDLE)
	{

	}
	else if (mAnchor & UIAllignment::BOT_LEFT)
	{

	}
	else //if (mAnchor & UIAllignment::CENTER) //DEFAULT ALLIGNMENT
	{

	}
}