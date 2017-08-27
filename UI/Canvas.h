#pragma once
#include <vector>
#include <glew.h>
#include "iUIElement.h"

class Canvas
{
public:
	Canvas();
	~Canvas();

	void AddElement(iUIElement* ele, GLuint layer = 0);

	void Draw();
private:
	std::vector<std::vector<iUIElement*>> mCanvasElements;

	GLuint mShader;
	GLuint mUniformLocation;
	
};

