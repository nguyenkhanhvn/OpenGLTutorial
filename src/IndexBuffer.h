#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class IndexBuffer
{
public:
	// Properties
	GLuint Id;


	// Method
	IndexBuffer(GLsizeiptr size, const void* data, GLenum usage);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

private:
	// Properties



	// Method
};

