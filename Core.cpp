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
#include "Chunk.h"
#include "Section.h"
//#include "Input.h"

#include "UI/Canvas.h"
#include "UI/Label.h"
#include <string>

Core::Core(Window* window) : _window(window)
{

}


Core::~Core()
{
}

bool Core::Init()
{


	std::vector<GLfloat> posData;
	for (size_t x = 0; x < 4; ++x)
	{
		for (size_t z = 0; z < 4; ++z)
		{
			Chunk* chunk = new Chunk(x, z);
			auto data = chunk->GetChunkCubePosList();
			posData.insert(posData.end(), data.begin(), data.end());
		}
	}

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	GLuint posBuffer;
	glGenBuffers(1, &posBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, posBuffer);
	glBufferData(GL_ARRAY_BUFFER, posData.size() * sizeof(GLfloat), &posData[0], GL_STATIC_DRAW);

	GLuint cubeBuffer;
	glGenBuffers(1, &cubeBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, cubeBuffer);
	glBufferData(GL_ARRAY_BUFFER, CubeData::mVertices.size() * sizeof(GLfloat), &CubeData::mVertices[0], GL_STATIC_DRAW);

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
	
	Label* fps = new Label("FPS: Like... a lot", 0, 685, 35);
	Label* label = new Label("Mike sucks dick", 0, 0, 16);

	Canvas* canvas = new Canvas();
	canvas->AddElement(fps);
	canvas->AddElement(label);

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
			//fps->ChangeText();
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
		//glEnable(GL_CULL_FACE);
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
		
		glm::mat4 mvp = projection * view * Model;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

		glVertexAttribDivisor(1, 1);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

		//glDrawElements(GL_TRIANGLES, CubeData::mIndices.size(), GL_UNSIGNED_SHORT, 0);
		glDrawElementsInstanced(GL_TRIANGLES, CubeData::mIndices.size(), GL_UNSIGNED_SHORT, 0, posData.size() / 3);


		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glVertexAttribDivisor(1, 0);

		glDisable(GL_DEPTH_TEST);
		canvas->Draw();


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
