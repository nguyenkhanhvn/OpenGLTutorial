#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VertexBuffer
{
public:
	// Properties
	GLuint Id;


	// Method
	VertexBuffer(GLsizeiptr size, const void* data, GLenum usage);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

private:
	// Properties



	// Method
};

