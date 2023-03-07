#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "Shader.h"
#include "Camera.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"


class Mesh
{
public:
	// Properties
	VertexArray VA;
	std::vector<Vertex> Vertices;
	std::vector<GLuint> Indices;
	std::vector<Texture> Textures;


	// Method
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
	~Mesh();

	void Draw(Shader& shader, Camera& camera);

private:
	// Properties
	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
};

