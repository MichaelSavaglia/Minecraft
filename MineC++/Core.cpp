#include "Core.h"

#include <glm.hpp>

#include <vector>
#include <iostream>
#include <glew.h>
#include <glfw3.h>

#include "Shaders/ShaderLoader.h"
#include "Camera.h"
#include "CubeData.h"
#include "Chunk.h"
#include "Cube.h"
#include "Input.h"

Core::Core(Window* window) : _window(window)
{

}


Core::~Core()
{
}

bool Core::Init()
{

	Chunk* chunk = new Chunk();
	chunk->GenerateCubeData();

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);


	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, chunk->mChunkMesh.size() * sizeof(GLfloat), &chunk->mChunkMesh[0], GL_STATIC_DRAW);

	/*GLuint colorBuffer;
	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, chunk->mChunkColours.size() * sizeof(GLfloat), &chunk->mChunkColours[0], GL_STATIC_DRAW);*/

	GLuint uvBuffer;
	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, chunk->mChunkUVs.size() * sizeof(GLfloat), &chunk->mChunkUVs[0], GL_STATIC_DRAW);

	GLuint indexBuffer;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, chunk->mChunkIndices.size() * sizeof(unsigned short), &chunk->mChunkIndices[0], GL_STATIC_DRAW);


	GLuint ProgramID;
	ProgramID = ShaderUtil::LoadShaders("Shaders/VertexShader.glsl", "Shaders/FragmentShader.glsl");

	glm::mat4 Model = glm::mat4(1.0f);

	GLuint MatrixID = glGetUniformLocation(ProgramID, "MVP");

	Camera* cam = new Camera(_window->GetGLFWWindow());
	
	GLuint textureID;// = SOIL_load_OGL_texture("Textures/dirt.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		int width, height;
		unsigned char* image = SOIL_load_image("Textures/dirt.png", &width, &height, 0, SOIL_LOAD_RGB);// SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
	GLuint TextureSampler = glGetUniformLocation(ProgramID, "myTextureSampler");
	
	double lastTime = glfwGetTime();
	int nbFrames = 0;
	do
	{
		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
												// printf and reset timer
			printf("%f ms/frame\n", 1000.0 / double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}

		if (Input::Instance()->GetKeyPressed(GLFW_KEY_1))
		{
			printf("Key Pressed \n");
		}

		cam->Update(true);
		auto projection = cam->GetProjectionMatrix();
		auto view = cam->GetViewMatrix();
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(ProgramID);

		glBindTexture(GL_TEXTURE_2D, textureID);
		glUniform1i(TextureSampler, 0);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		
		glm::mat4 mvp = projection * view * Model;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glDrawElements(GL_TRIANGLES, chunk->mChunkIndices.size(), GL_UNSIGNED_SHORT, 0);

		glDisableVertexAttribArray(0);
		

		glfwSwapBuffers(_window->GetGLFWWindow());
		glfwPollEvents();
	} while (glfwGetKey(_window->GetGLFWWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(_window->GetGLFWWindow()) == 0);

	return true;
}

void Core::LoadObjects()
{
}

void Core::MainLoop()
{
}

void Core::Draw()
{
}

void Core::Update()
{
}

void Core::Input()
{
}
