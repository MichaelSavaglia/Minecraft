#include "Core.h"

#include <glm.hpp>

#include <vector>
#include <iostream>
#include <glew.h>
#include <glfw3.h>

#include "Shaders/ShaderLoader.h"
#include "Camera.h"
#include "CubeData.h"
#include "Cube.h"
#include "Section.h"
//#include "Input.h"

Core::Core(Window* window) : _window(window)
{

}


Core::~Core()
{
}

bool Core::Init()
{

	std::vector<GLfloat> posData;
	for (size_t i = 0; i < 16; ++i)
	{
		Section* testSect = new Section(i);
		auto data = testSect->GenPosData();
		posData.insert(posData.end(), data.begin(), data.end());
	}

	static const GLfloat arr[] = 
	{
		0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,10.0f,11.0f,12.0f,13.0f,14.0f,15.0f
	};

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);


	GLuint posBuffer;
	glGenBuffers(1, &posBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, posBuffer);
	glBufferData(GL_ARRAY_BUFFER, posData.size() * sizeof(GLfloat), &posData[0], GL_STATIC_DRAW);

	GLuint cubeBuffer;
	glGenBuffers(1, &cubeBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, cubeBuffer);
	glBufferData(GL_ARRAY_BUFFER, CubeData::mVertices.size() * sizeof(GLfloat), &CubeData::mVertices[0], GL_STATIC_DRAW);

	GLuint yBuffer;
	glGenBuffers(1, &yBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, yBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(arr), arr, GL_STATIC_DRAW);


	GLuint indexBuffer;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, CubeData::mIndices.size() * sizeof(unsigned short), &CubeData::mIndices[0], GL_STATIC_DRAW);
	
	GLuint ProgramID;
	ProgramID = ShaderUtil::LoadShaders("Shaders/VertexShader.glsl", "Shaders/FragmentShader.glsl");

	glm::mat4 Model = glm::mat4(1.0f);

	GLuint MatrixID = glGetUniformLocation(ProgramID, "MVP");

	Camera* cam = new Camera(_window->GetGLFWWindow());
	
	GLuint textureID;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		int width, height;
		unsigned char* image = SOIL_load_image("Textures/dirt.png", &width, &height, 0, SOIL_LOAD_RGB);// SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
	GLuint TextureSampler = glGetUniformLocation(ProgramID, "myTextureSampler");
	GLuint textureSheet = SOIL_load_OGL_texture(
		"Textures/texturesheet.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	

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

		//if (Input::Instance()->GetKeyPressed(GLFW_KEY_1))
		//{
		//	printf("Key Pressed \n");
		//}

		cam->Update(true);
		auto projection = cam->GetProjectionMatrix();
		auto view = cam->GetViewMatrix();
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(ProgramID);

	/*	glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureSheet);
		glUniform1i(TextureSampler, 0);*/

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, cubeBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, posBuffer);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, yBuffer);
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
		
		glm::mat4 mvp = projection * view * Model;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

		glVertexAttribDivisor(1, 1);
		glVertexAttribDivisor(2, 4096);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

		//glDrawElements(GL_TRIANGLES, CubeData::mIndices.size(), GL_UNSIGNED_SHORT, 0);
		glDrawElementsInstanced(GL_TRIANGLES, CubeData::mIndices.size(), GL_UNSIGNED_SHORT, 0, 4096 * 16);


		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);


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
