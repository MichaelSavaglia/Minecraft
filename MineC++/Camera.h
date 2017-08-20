#pragma once

#include <glm.hpp>
struct GLFWwindow;

class Camera
{
public:
	Camera(GLFWwindow* window);
	~Camera();

	void Update(bool active);

	inline glm::mat4 GetViewMatrix()		const { return mViewMatrix; }
	inline glm::mat4 GetProjectionMatrix()	const { return mProjectionMatrix; }


private:
	GLFWwindow* mWindow;

	glm::mat4 mViewMatrix;
	glm::mat4 mProjectionMatrix;

	glm::vec3 mPos;
	float mHorizontalAngle = 3.141f; // TODO: Add these variables to constructor
	float mVerticalAngle = 0.0f;

	float mInitialFoV = 45.0f;
	float mSpeed = 10.0f;
	float mMouseSpeed = 0.05f;
};

