#include "Texture.h"

#include <stb/stb_image.h>

#include "common.h"
#include "Shader.h"

Texture::Texture(const char* path, const char* type, GLuint unit, GLenum textureTarget, GLenum pixelType, int desiredChannels):
	Id(0), Type(type), m_unit(unit), m_textureTarget(textureTarget), m_width(0), m_height(0), m_numColCh(0)
{
	stbi_set_flip_vertically_on_load(1);
	unsigned char* textureData = stbi_load(path, &m_width, &m_height, &m_numColCh, desiredChannels);

	GLCall(glGenTextures(1, &Id));
	GLCall(glActiveTexture(GL_TEXTURE0 + m_unit));
	GLCall(glBindTexture(textureTarget, Id));

	// Configures the type of algorithm that is used to make the image smaller or bigger
	GLCall(glTexParameteri(textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	// Configures the way the texture repeats (if it does at all)
	GLCall(glTexParameteri(textureTarget, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(textureTarget, GL_TEXTURE_WRAP_T, GL_REPEAT));

	if (m_numColCh == 4)
	{
		GLCall(glTexImage2D(textureTarget, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, pixelType, textureData));
	}
	else if (m_numColCh == 3)
	{
		GLCall(glTexImage2D(textureTarget, 0, GL_RGBA, m_width, m_height, 0, GL_RGB, pixelType, textureData));
	}
	else if (m_numColCh == 1)
	{
		GLCall(glTexImage2D(textureTarget, 0, GL_RGBA, m_width, m_height, 0, GL_RED, pixelType, textureData));
	}
	else
	{
		GLCall(glTexImage2D(textureTarget, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, pixelType, textureData));
	}




	GLCall(glGenerateMipmap(textureTarget));

	// Deletes the image data as it is already in the OpenGL Texture object
	if (textureData)
		stbi_image_free(textureData);

	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	GLCall(glBindTexture(textureTarget, 0));

}

void Texture::Bind() const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + m_unit));
	GLCall(glBindTexture(m_textureTarget, Id));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(m_textureTarget, 0));
}

void Texture::TexUnit(class Shader& shader, std::string uniformName)
{
	GLCall(glActiveTexture(GL_TEXTURE0 + m_unit));
	shader.Bind();
	shader.SetUniform1i(uniformName, m_unit);
}

void Texture::Delete() const
{
	GLCall(glDeleteTextures(1, &Id));
}
