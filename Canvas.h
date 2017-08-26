#pragma once
#include <vector>
#include <glew.h>

class Canvas
{
public:
	Canvas();
	~Canvas();

	void Draw(const char* text, int x, int y, int size);

private:
	std::vector<GLfloat> mCanvas;

	GLuint mShader;
	GLuint mVertexBuffer;
	GLuint mUVBuffer;
	GLuint mUniformLocation;
	GLuint mTexture;
};

