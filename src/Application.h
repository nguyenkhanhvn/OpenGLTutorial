#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include "imgui.h"

class Application
{
public:
	// Properties
	unsigned int Width, Height;
	std::string Title;


	// Methods
	Application(std::string title, unsigned int width = 800, unsigned int height = 800);
	virtual ~Application();

	virtual int run();

private:
	// Properties
	GLFWwindow* m_window;
	const char* m_glsl_version;
	ImGuiIO* m_io;


	// Methods

};

