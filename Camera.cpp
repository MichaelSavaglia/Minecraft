#include "Camera.h"
#include "Window.h"
#include <glfw3.h>

#include <gtc/matrix_transform.hpp>


Camera::Camera(GLFWwindow* window) : mWindow(window) 
{
	mPos = glm::vec3(0.0f, 0.0f, 0.0f);
};
Camera::~Camera()
{
}

void Camera::Update(bool active)
{
	static double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	int width, height;
	glfwGetWindowSize(mWindow, &width, &height);

	double xpos, ypos;
	if (active == true)
	{
		glfwGetCursorPos(mWindow, &xpos, &ypos);

		glfwSetCursorPos(mWindow, width / 2, height / 2);


		mHorizontalAngle += mMouseSpeed * deltaTime * float(width / 2 - xpos);
		mVerticalAngle += mMouseSpeed * deltaTime * float(height / 2 - ypos);
	}

	 mDir = glm::vec3(
		cos(mVerticalAngle) * sin(mHorizontalAngle),
		sin(mVerticalAngle),
		cos(mVerticalAngle) * cos(mHorizontalAngle));

	glm::vec3 right(
		sin(mHorizontalAngle - 3.14f / 2.0f),
		0,
		cos(mHorizontalAngle - 3.14f / 2.0f));

	glm::vec3 up = glm::cross(right, mDir);


	if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS)
		mPos += mDir * deltaTime * mSpeed;
	if (glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS)
		mPos -= mDir * deltaTime * mSpeed;
	if (glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_PRESS)
		mPos -= right * deltaTime * mSpeed;
	if (glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_PRESS)
		mPos += right * deltaTime * mSpeed;

	mProjectionMatrix = glm::perspective(mInitialFoV, 4.0f / 3.0f, 0.1f, 300.0f);

	mViewMatrix = glm::lookAt(
		mPos,
		mPos + mDir,
		up);

	lastTime = currentTime;
}