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

#include "Input.h"

#include "UI/Canvas.h"
#include "UI/Label.h"
#include "UI/Button.h"
#include "UI/Image.h"
#include <string>

Core::Core(Window* window) : _window(window)
{
	/*textureAtlas = new TextureAtlas();
	textureAtlas->LoadTextureAtlas("Textures/dirt.png", 64, 64, 64, 64);*/
}


Core::~Core()
{

}

bool Core::Init()
{
	std::vector<GLint> posData;
	std::vector<Chunk*> chunks;
	for (size_t x = 0; x < 4; ++x)
	{
		for (size_t z = 0; z < 4; ++z)
		{
			auto chunk = new Chunk(x, z);
			chunks.push_back(chunk);
			auto data = chunk->GetChunkCubePosList();
			posData.insert(posData.end(), data.begin(), data.end()); // TEMPORARY AS WE OBVIOUSLY DONT WANT TO STORE THIS DATA TWICE
		}
	}
	posData.shrink_to_fit();

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	GLuint posBuffer;
	glGenBuffers(1, &posBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, posBuffer);
	glBufferData(GL_ARRAY_BUFFER, posData.size() * sizeof(GLint), &posData[0], GL_STATIC_DRAW);

	GLuint cubeBuffer;
	glGenBuffers(1, &cubeBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, cubeBuffer);
	glBufferData(GL_ARRAY_BUFFER, CubeData::mVertices.size() * sizeof(GLfloat), &CubeData::mVertices[0], GL_STATIC_DRAW);

	GLuint textureBuffer;
	glGenBuffers(1, &textureBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	glBufferData(GL_ARRAY_BUFFER, CubeData::mUVs.size() * sizeof(GLfloat), &CubeData::mUVs[0], GL_STATIC_DRAW);

	
	GLuint textureIndexBuffer;
	glGenBuffers(1, &textureIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, textureIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, CubeData::mIndices.size() * sizeof(unsigned short), &CubeData::mIndices[0], GL_STATIC_DRAW);
	
	GLuint ProgramID;
	ProgramID = ShaderUtil::LoadShaders("Shaders/VertexShader.glsl", "Shaders/FragmentShader.glsl");

	glm::mat4 Model = glm::mat4(1.0f);

	GLuint MatrixID = glGetUniformLocation(ProgramID, "MVP");

	Camera* cam = new Camera(_window->GetGLFWWindow());
	

	GLuint TextureSampler = glGetUniformLocation(ProgramID, "myTextureSampler");
	GLuint textureSheet = SOIL_load_OGL_texture(
		"Textures/dirt.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,0
	);
	
	int clicks = 0;
	Label* fps = new Label("FPS: Like... a lot", 0, 685, 35);
	Label* position = new Label("X: 0, Y: 0, Z: 0", 0, 660, 25);
	Label* label = new Label("Press 1 to toggle camera", 0, 500, 32);
	//Button* button = new Button("Textures/dirt.png", 500, 300, 100, 100, "A button");
	////Image* img = new Image("Textures/dirt.png", 300, 300, 50, 50);
	////img->SetPosition(500, 500);
	//button->BindOnClick([&]() {
	//	std::string text = std::to_string(++clicks);
	//	button->ChangeText(text);
	//});
	//button->BindOnRelease([&]() {
	//	std::string text = std::to_string(--clicks);
	//	button->ChangeText(text);
	//});
	//button->SetAllignment(UIAllignment::BOT_LEFT);

	Canvas* canvas = new Canvas();
	canvas->AddElement(fps);
	canvas->AddElement(label);
	canvas->AddElement(position);
	//canvas->AddElement(button);
	//canvas->AddElement(img);

	bool camActive = false;
	double lastTime = glfwGetTime();
	int nbFrames = 0;
	glm::vec3 camPos;
	do
	{
		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
												// printf and reset timer
			printf("%f ms/frame\n", 1000.0 / double(nbFrames));
			fps->ChangeText(std::to_string(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}
		
		camPos = cam->GetPos();
		position->ChangeText("X:" + std::to_string(camPos.x) + ", Y: " + std::to_string(camPos.y) + ", Z: " + std::to_string(camPos.z));

		if (Input::Instance()->GetKeyPressed(GLFW_KEY_1))
		{
			if (camActive)
			{
				camActive = false;
				glfwSetInputMode(_window->GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
			else
			{
				camActive = true;
				glfwSetInputMode(_window->GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

			}
		}

		cam->Update(camActive);
		auto projection = cam->GetProjectionMatrix();
		auto view = cam->GetViewMatrix();
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glClearColor(0.529, 0.807, 0.980, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(ProgramID);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureSheet);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glUniform1i(TextureSampler, 0);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, cubeBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, posBuffer);
		glVertexAttribIPointer(1, 3, GL_INT, 0, (void*)0);

		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		
		glm::mat4 mvp = projection * view * Model;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

		glVertexAttribDivisor(1, 1);


		glDrawArraysInstanced(GL_TRIANGLES, 0, CubeData::mVertices.size(), posData.size() / 3);


		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glVertexAttribDivisor(1, 0);


		//button->Update();
		glDisable(GL_DEPTH_TEST);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		canvas->Draw();


		Input::Instance()->ClearKeyBuffer();
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
