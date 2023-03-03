#include "Camera.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include "Shader.h"

Camera::Camera(GLsizei width, GLsizei height, glm::vec3 postion, glm::vec3 orientation, glm::vec3 up, float FOVdeg, float nearPlane, float farPlane):
	Width(width), Height(height), Position(postion), Orientation(orientation), Up(up), m_proj(glm::mat4(1.0f)), m_firstClick(false)
{
	m_proj = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);
}

void Camera::SetupPerspective(float FOVdeg, float nearPlane, float farPlane)
{
	m_proj = glm::perspective(glm::radians(FOVdeg), (float)Width / Height, nearPlane, farPlane);
}

void Camera::Input(GLFWwindow* window)
{
	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += Speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += Speed * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += Speed * glm::cross(Up, Orientation);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += Speed * -glm::cross(Up, Orientation);
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		Position += Speed * Up;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		Position += Speed * -Up;
	}

	// Handles mouse inputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		if (m_firstClick) {
			m_firstClick = false;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			glfwSetCursorPos(window, Width / 2, Height / 2);
		}

		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotX = Sensitivity * (float)(mouseY - (Height / 2)) / Height;
		float rotY = Sensitivity * (float)(mouseX - (Width / 2)) / Width;

		// Rotate Up/Down
		glm::vec3 newOrientation = glm::rotate(Orientation, rotX, glm::normalize(glm::cross(Up, Orientation)));
		if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
			Orientation = newOrientation;

		// Rotate Left/Right
		Orientation = glm::rotate(Orientation, -rotY, Up);

		glfwSetCursorPos(window, Width / 2, Height / 2);
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		m_firstClick = true;
	}
}

void Camera::Use(Shader& shader, const GLchar* cameraUniform)
{
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(Position, Position + Orientation, Up);
	shader.SetUniformMat4f(cameraUniform, m_proj * view);
}
