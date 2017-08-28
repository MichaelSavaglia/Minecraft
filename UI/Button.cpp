#include "Button.h"
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
	

	//not sure if what i did was correct but you need to define background texture more clearly
	//iUIElement::Draw(); ?? 

	mLabel->Draw();
}