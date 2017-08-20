#pragma once
#include <glew.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <glew.h>
#include <glfw3.h>
#include <iostream>
namespace ShaderUtil
{
	GLuint LoadShaders(const char* VertexPath, const char* FragmentPath);
}