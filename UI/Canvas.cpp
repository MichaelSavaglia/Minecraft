#include "Canvas.h"
#include "..\Shaders\ShaderLoader.h"
#include <SOIL.h>
#include <glfw3.h>

Canvas::Canvas()
{
	mShader = ShaderUtil::LoadShaders("Shaders/UIVertexShader.glsl", "Shaders/UIFragmentShader.glsl");
	glUseProgram(mShader);
	mUniformLocation = glGetUniformLocation(mShader, "myTextureSampler");
	mCanvasElements = std::vector<std::vector<iUIElement*>>();
	mCanvasElements.resize(1);
}

Canvas::~Canvas()
{
	glDeleteProgram(mShader);
}

void Canvas::AddElement(iUIElement * ele, GLuint layer)
{
	if (mCanvasElements.size() + 1 < layer)
	{
		mCanvasElements.resize(layer);
	}

	mCanvasElements.at(layer).push_back(ele);
}

void Canvas::Draw()
{
	glUseProgram(mShader);
	
	for (int layer = 0; layer < mCanvasElements.size(); ++layer)
	{
		for (auto element : mCanvasElements[layer])
		{
			glUniform1i(mUniformLocation, 0);
			element->Draw();
		}
	}
	
}