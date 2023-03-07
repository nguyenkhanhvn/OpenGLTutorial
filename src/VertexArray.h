#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VertexArray
{
public:
	// Properties
	GLuint Id;


	// Method
	VertexArray();

	void Bind() const;
	void Unbind() const;

	void Delete() const;

	void AddBuffer(const class VertexBuffer& vb, const class VertexBufferLayout& layout);

private:
	// Properties



	// Method
};

