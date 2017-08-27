#pragma once
#include <glew.h>
#include <vector>
#include <glm.hpp>

class iUIElement
{
public:
	iUIElement(); 
	virtual ~iUIElement();
	virtual void Draw() = 0;
	inline GLuint GetTextureID() { return mTexture; };

private:

protected:
	GLuint mVertexBuffer;
	GLuint mUVBuffer;
	GLuint mTexture;

	std::vector<glm::vec2> vertices;
	std::vector<glm::vec2> UVs;
};

