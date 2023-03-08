#include "Mesh.h"

#include<glm/gtc/matrix_transform.hpp>

#include <string>

#include "common.h"
#include "VertexBufferLayout.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures) :
	Vertices(vertices), Indices(indices), Textures(textures)
{
	VA.Bind();

	m_vb = new VertexBuffer(vertices);
	VertexBufferLayout layout;
	layout.Push({ GL_FLOAT, 3, GL_FALSE });
	layout.Push({ GL_FLOAT, 3, GL_FALSE });
	layout.Push({ GL_FLOAT, 3, GL_FALSE });
	layout.Push({ GL_FLOAT, 2, GL_FALSE });
	VA.AddBuffer(*m_vb, layout);

	m_ib = new IndexBuffer(indices);

	VA.Unbind();
	m_vb->Unbind();
	m_ib->Unbind();
}

void Mesh::Delete() const
{
	m_ib->Unbind();
	m_ib->Delete();
	m_vb->Unbind();
	m_vb->Delete();
	VA.Unbind();
	VA.Delete();
}

void Mesh::DrawSimple(Shader& shader, Camera& camera)
{
	shader.Bind();
	VA.Bind();

	camera.Use(shader);

	// Draw the actual mesh
	GLCall(glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0));
}

void Mesh::Draw(Shader& shader, Camera& camera, glm::mat4 matrix, glm::vec3 translation, glm::quat rotation, glm::vec3 scale)
{
	shader.Bind();
	VA.Bind();

	unsigned int numDiffuse = 0, numSpecular = 0;

	for (size_t i = 0; i < Textures.size(); i++)
	{
		std::string type = Textures[i].Type;
		std::string uniform = type;
		if (type == "diffuse")
		{
			uniform += std::to_string(numDiffuse++);
		}
		else if (type == "specular")
		{
			uniform += std::to_string(numSpecular++);
		}
		Textures[i].TexUnit(shader, uniform);
		Textures[i].Bind();
	}

	camera.Use(shader);

	// Initialize matrices
	glm::mat4 trans = glm::mat4(1.0f);
	glm::mat4 rot = glm::mat4(1.0f);
	glm::mat4 sca = glm::mat4(1.0f);

	// Transform the matrices to their correct form
	trans = glm::translate(trans, translation);
	rot = glm::mat4_cast(rotation);
	sca = glm::scale(sca, scale);

	// Push the matrices to the vertex shader
	shader.SetUniformMat4f("model", matrix);
	shader.SetUniformMat4f("translation", trans);
	shader.SetUniformMat4f("rotation", rot);
	shader.SetUniformMat4f("scale", sca);

	// Draw the actual mesh
	GLCall(glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0));
}
