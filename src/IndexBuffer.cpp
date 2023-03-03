#include "IndexBuffer.h"

#include "common.h"

IndexBuffer::IndexBuffer(GLsizeiptr size, const void* data, GLenum usage):
	Id(0)
{
	GLCall(glGenBuffers(1, &Id));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Id));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage));
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &Id));
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Id));
}

void IndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
