#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include <unordered_map>

class Texture
{
public:
	// Properties
	GLuint Id;


	// Method
	Texture(const char* path, GLenum textureType, GLenum format, GLenum pixelType, int desiredChannels = 0);
	~Texture();

	void Bind() const;
	void Unbind() const;

	void TexUnit(class Shader& shader, const GLchar* uniformName, GLuint unit);

private:
	// Properties
	GLenum m_type;
	int m_width;
	int m_height;
	int m_numColCh;


	// Method
};

