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
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

private:
	// Properties



	// Method
};

