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
	const char* Type;


	// Method
	Texture(const char* path, const char* type, GLuint unit, GLenum textureTarget, GLenum format, GLenum pixelType, int desiredChannels = 0);
	~Texture();

	void Bind() const;
	void Unbind() const;

	void TexUnit(class Shader& shader, const GLchar* uniformName);

private:
	// Properties
	GLuint m_unit;
	GLenum m_textureTarget;
	int m_width;
	int m_height;
	int m_numColCh;


	// Method
};

