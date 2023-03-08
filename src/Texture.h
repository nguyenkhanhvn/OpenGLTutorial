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
	Texture(const char* path, const char* type, GLuint unit, GLenum textureTarget = GL_TEXTURE_2D, GLenum pixelType = GL_UNSIGNED_BYTE, int desiredChannels = 0);

	void Bind() const;
	void Unbind() const;

	void TexUnit(class Shader& shader, std::string uniformName);

	void Delete() const;

private:
	// Properties
	GLuint m_unit;
	GLenum m_textureTarget;
	int m_width;
	int m_height;
	int m_numColCh;


	// Method
};

