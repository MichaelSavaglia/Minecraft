#include "Button.h"
#include <SOIL.h>
#include "Label.h"
#include "../TextureManager.h"

Button::Button(const char* texturePath, int x, int y, int width, int height, std::string text) : iUIElement(x, y, width, height)
{
	mTexture = TextureManager::Instance()->LoadTexture(texturePath);

	mLabel = new Label(text, x, y, height);
}


Button::~Button()
{

}


void Button::Update()
{
	std::invoke(mOnClick);
}

void Button::Draw()
{
	if (mBufferNeedsUpdate)
	{
		SetBuffers();
		mBufferNeedsUpdate = false;
	}

	iUIElement::Draw();
	mLabel->Draw();
}