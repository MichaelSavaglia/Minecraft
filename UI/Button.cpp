#include "Button.h"
#include <SOIL.h>
#include "Label.h"

Button::Button(const char* texturePath, int x, int y, int width, int height, std::string text) : iUIElement(x, y, width, height)
{
	mTexture = SOIL_load_OGL_texture(
		texturePath,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
	);

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