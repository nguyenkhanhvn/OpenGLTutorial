#include "VertexBuffer.h"

#include "common.h"

VertexBuffer::VertexBuffer(std::vector<Vertex> vertices, GLenum usage):
	Id(0)
{
	GLCall(glGenBuffers(1, &Id));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, Id));
	GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), usage));
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &Id));
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, Id));
}

void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
