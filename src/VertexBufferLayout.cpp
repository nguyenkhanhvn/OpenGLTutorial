#include "VertexBufferLayout.h"

unsigned int VertexBufferLayoutElement::GetSizeOfType(GLenum type)
{
	switch (type)
	{
	case GL_FLOAT: return 4;
	case GL_UNSIGNED_INT: return 4;
	case GL_UNSIGNED_BYTE: return 1;
	default: return 0;
	}
}


void VertexBufferLayout::Push(GLenum type, GLint size, GLboolean normalized)
{
	m_elements.push_back({ size, type, normalized });
	m_stride += size * VertexBufferLayoutElement::GetSizeOfType(type);
}
