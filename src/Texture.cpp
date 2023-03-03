#include "Texture.h"

#include <stb/stb_image.h>

#include "common.h"
#include "Shader.h"

Texture::Texture(const char* path, GLenum textureType, GLenum format, GLenum pixelType, int desiredChannels):
	Id(0), m_type(textureType), m_width(0), m_height(0), m_numColCh(0)
{
	stbi_set_flip_vertically_on_load(1);
	unsigned char* textureData = stbi_load(path, &m_width, &m_height, &m_numColCh, desiredChannels);

	GLCall(glGenTextures(1, &Id));
	GLCall(glBindTexture(textureType, Id));

	// Configures the type of algorithm that is used to make the image smaller or bigger
	GLCall(glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	// Configures the way the texture repeats (if it does at all)
	GLCall(glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_REPEAT));

	GLCall(glTexImage2D(textureType, 0, GL_RGBA8, m_width, m_height, 0, format, pixelType, textureData));

	//GLCall(glGenerateMipmap(textureType));

	// Deletes the image data as it is already in the OpenGL Texture object
	if (textureData)
		stbi_image_free(textureData);

	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	GLCall(glBindTexture(textureType, 0));

}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &Id));
}

void Texture::Bind() const
{
	GLCall(glBindTexture(m_type, Id));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(m_type, 0));
}

void Texture::TexUnit(class Shader& shader, const GLchar* uniformName, GLuint unit)
{
	GLCall(glActiveTexture(GL_TEXTURE0 + unit));
	shader.Bind();
	shader.SetUniform1i(uniformName, unit);
}
