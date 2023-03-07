#include "VertexArray.h"

#include "common.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray():
	Id(0)
{
	GLCall(glGenVertexArrays(1, &Id));
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(Id));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}

void VertexArray::Delete() const
{
	GLCall(glDeleteVertexArrays(1, &Id));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();

	const auto elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		auto element = elements[i];
		GLCall(glVertexAttribPointer(i, element.size, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		GLCall(glEnableVertexAttribArray(i));
		offset += element.size * VertexBufferLayoutElement::GetSizeOfType(element.type);
	}
}
