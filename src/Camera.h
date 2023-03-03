#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

class Camera
{
public:
	// Properties
	int Width;
	int Height;

	glm::vec3 Position;
	glm::vec3 Orientation;
	glm::vec3 Up;

	float Speed = 0.02f;
	float Sensitivity = 0.5f;


	// Method
	Camera(GLsizei width, GLsizei height, glm::vec3 postion, glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float FOVdeg = 45, float nearPlane = 0.1f, float farPlane = 100.0f);

	void SetupPerspective(float FOVdeg, float nearPlane, float farPlane);

	void Input(GLFWwindow* window);

	void Use(class Shader& shader, const GLchar* cameraUniform);

private:
	// Properties
	glm::mat4 m_proj;

	bool m_firstClick;


	// Method
};

