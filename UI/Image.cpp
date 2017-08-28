#include "Image.h"
#include "../TextureManager.h"


Image::Image(const char* texturePath, int x, int y, int width, int height) :iUIElement(x,y,width,height)
{
	mTexture = TextureManager::Instance()->LoadTexture(texturePath);
}


Image::~Image()
{
}

void Image::Draw()
{
	SetBuffers();
	iUIElement::Draw();
}
