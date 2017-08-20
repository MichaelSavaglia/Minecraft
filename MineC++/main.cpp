#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\glfw\glfw3.h"
#include <iostream>

int main(int argc, char** argv)
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialise GLFW" << std::endl;

		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window;

	window = glfwCreateWindow(1024, 768, "MineC++", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to open GLFW Window" << std::endl;

		glfwTerminate();

		return -1;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = true;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialise GLEW" << std::endl;
		return -1;
	}

	return 0;
}