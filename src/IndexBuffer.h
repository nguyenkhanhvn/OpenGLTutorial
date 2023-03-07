#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

class IndexBuffer
{
public:
	// Properties
	GLuint Id;


	// Method
	IndexBuffer(std::vector<GLuint> indices, GLenum usage = GL_STATIC_DRAW);

	void Bind() const;
	void Unbind() const;

	void Delete() const;

private:
	// Properties



	// Method
};

