#pragma once
#include "iUIElement.h"

class Image : public iUIElement
{
public:
	Image(const char* texturePath, int x, int y, int width, int height);
	~Image();

	virtual void Draw();
private:
};

