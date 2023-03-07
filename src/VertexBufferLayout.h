#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

struct VertexBufferLayoutElement
{
	GLenum type;
	GLint size;
	GLboolean normalized;

	static unsigned int GetSizeOfType(GLenum type);
};

class VertexBufferLayout
{
public:
	// Properties
	GLuint Id;


	// Method
	void Push(const VertexBufferLayoutElement& layout);
	
	inline std::vector<VertexBufferLayoutElement> GetElements() const { return m_elements; }
	inline GLsizei GetStride() const { return m_stride; }

private:
	// Properties
	std::vector<VertexBufferLayoutElement> m_elements;
	GLsizei m_stride;


	// Method
};

