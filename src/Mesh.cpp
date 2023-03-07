#include "Mesh.h"

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

Mesh::~Mesh()
{
	m_ib->Unbind();
	m_ib->Delete();
	m_vb->Unbind();
	m_vb->Delete();
	VA.Unbind();
	VA.Delete();
}

void Mesh::Draw(Shader& shader, Camera& camera)
{
	shader.Bind();

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
	VA.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0));
}
