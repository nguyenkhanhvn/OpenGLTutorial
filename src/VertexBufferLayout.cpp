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


void VertexBufferLayout::Push(const VertexBufferLayoutElement& layout)
{
	m_elements.push_back(layout);
	m_stride += layout.size * VertexBufferLayoutElement::GetSizeOfType(layout.type);
}
