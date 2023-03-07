#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};

class VertexBuffer
{
public:
	// Properties
	GLuint Id;


	// Method
	VertexBuffer(std::vector<Vertex> vertices, GLenum usage = GL_STATIC_DRAW);

	void Bind() const;
	void Unbind() const;

	void Delete() const;

private:
	// Properties



	// Method
};

