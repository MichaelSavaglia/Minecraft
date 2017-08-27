#include "Button.h"
#include "Label.h"

Button::Button(const char* texturePath, std::function<void()> func)
{
	mOnClick = std::bind(func);
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

}