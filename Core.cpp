#include "Core.h"

#include <glm.hpp>

#include <vector>
#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include <random>
#include "Shaders/ShaderLoader.h"
#include "Camera.h"
#include "CubeData.h"
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
	textureAtlas = TextureAtlas::Instance();
}


Core::~Core()
{

}

bool Core::Init()
{
	std::vector<GLint> posData;
	std::vector<GLfloat> textureData;
	std::vector<Chunk*> chunks;

	for (int x = 0; x < 21; ++x)
	{
		for (size_t z = 0; z < 21; ++z)
		{
			chunks.emplace_back(new Chunk(x, z));
			auto data = chunks[chunks.size()-1]->GetChunkCubePosList();
			auto texturedata = chunks[chunks.size()-1]->GetTextureData();
			posData.insert(posData.end(), data.begin(), data.end());
			textureData.insert(textureData.end(), texturedata.begin(), texturedata.end());
		}
	}

	textureData.shrink_to_fit();
	posData.shrink_to_fit();

	//Data up to this point is correct
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	GLuint posBuffer;
	glGenBuffers(1, &posBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, posBuffer);
	glBufferData(GL_ARRAY_BUFFER, posData.size() * sizeof(GLint), &posData[0], GL_STATIC_DRAW);

	GLuint textureoffsetBuffer;
	glGenBuffers(1, &textureoffsetBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, textureoffsetBuffer);
	glBufferData(GL_ARRAY_BUFFER, textureData.size() * sizeof(GLfloat), &textureData[0], GL_STATIC_DRAW);

	GLuint cubeBuffer;
	glGenBuffers(1, &cubeBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, cubeBuffer);
	glBufferData(GL_ARRAY_BUFFER, CubeData::mVertices.size() * sizeof(GLfloat), &CubeData::mVertices[0], GL_STATIC_DRAW);

	GLuint textureBuffer;
	glGenBuffers(1, &textureBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	glBufferData(GL_ARRAY_BUFFER, CubeData::mUVs.size() * sizeof(GLfloat), &CubeData::mUVs[0], GL_STATIC_DRAW);

	GLuint normalBuffer;
	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, CubeData::mNormals.size() * sizeof(GLfloat), &CubeData::mNormals[0], GL_STATIC_DRAW);

	
	GLuint indexBuffer;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, CubeData::mIndices.size() * sizeof(unsigned short), &CubeData::mIndices[0], GL_STATIC_DRAW);
	
	GLuint ProgramID;
	ProgramID = ShaderUtil::LoadShaders("Shaders/VertexShader.glsl", "Shaders/FragmentShader.glsl");

	glm::mat4 Model = glm::mat4(1.0f);

	GLuint MatrixID		= glGetUniformLocation(ProgramID, "MVP");
	GLuint ModelID		= glGetUniformLocation(ProgramID, "Model");
	GLuint ViewID		= glGetUniformLocation(ProgramID, "View");
	GLuint DiffuseID	= glGetUniformLocation(ProgramID, "material.diffuse");
	GLuint SpecularID	= glGetUniformLocation(ProgramID, "materlal.specular");


	Camera* cam = new Camera(_window->GetGLFWWindow());
	

	GLuint TextureSampler = glGetUniformLocation(ProgramID, "myTextureSampler");

	int clicks = 0;
	//Commented out as adding 3 seconds to load times
	Label* fps = new Label("FPS: Like... a lot", 0, 685, 35);
	Label* position = new Label("X: 0, Y: 0, Z: 0", 0, 660, 25);
	Label* label = new Label("Press 1 to toggle camera", 0, 600, 32);
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
	//canvas->AddElement(position);
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

		if (Input::Instance()->GetKeyPressed(GLFW_KEY_2))
		{
			textureAtlas->ReloadTextureAtlas();
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
		glBindTexture(GL_TEXTURE_2D, textureAtlas->GetTexture());

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

		glEnableVertexAttribArray(3);
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(4);
		glBindBuffer(GL_ARRAY_BUFFER, textureoffsetBuffer);
		glVertexAttribPointer(4, 3, GL_FLOAT,GL_FALSE, 0, (void*)0);

		glm::mat4 mvp = projection * view * Model;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

		auto camPos = cam->GetPos();
		glUniform3f(glGetUniformLocation(ProgramID, "eye"), camPos.x, camPos.y, camPos.z);

		glUniform3f(glGetUniformLocation(ProgramID, "light.direction"), 0.1f, -1.0f, 0.2f);
		glUniform3f(glGetUniformLocation(ProgramID, "light.ambient"), 0.15f, 0.15f, 0.15f);
		glUniform3f(glGetUniformLocation(ProgramID, "light.diffuse"), 0.5f, 0.5f, 0.5f);
		glUniform3f(glGetUniformLocation(ProgramID, "light.specular"), 0.2f, 0.2f, 0.2f);

		glUniform3f(glGetUniformLocation(ProgramID, "material.diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(ProgramID, "material.specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(ProgramID, "material.shininess"), 5.0f);

		glUniformMatrix4fv(ModelID, 1, GL_FALSE, &Model[0][0]);
		glUniformMatrix4fv(ViewID, 1, GL_FALSE, &view[0][0]);

		glVertexAttribDivisor(1, 1);
		glVertexAttribDivisor(4, 1);

		glDrawArraysInstanced(GL_TRIANGLES, 0, CubeData::mVertices.size(), posData.size() / 3);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		glDisableVertexAttribArray(4);
		glVertexAttribDivisor(1, 0);
		glVertexAttribDivisor(4, 0);



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
