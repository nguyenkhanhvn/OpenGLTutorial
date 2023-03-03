#include "Shader.h"

#include<glm/gtc/type_ptr.hpp>

#include "common.h"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath):
	Id(0)
{
	std::string vertSrc = get_file_contents(vertexShaderPath);
	std::string fragSrc = get_file_contents(fragmentShaderPath);
	GLuint vs = Shader::CompileShader(GL_VERTEX_SHADER, vertSrc);
	GLuint fs = Shader::CompileShader(GL_FRAGMENT_SHADER, fragSrc);

	GLCall(Id = glCreateProgram());
	GLCall(glAttachShader(Id, vs));
	GLCall(glAttachShader(Id, fs));

	GLCall(glLinkProgram(Id));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));
}

Shader::~Shader()
{

}

void Shader::Bind() const
{
	glUseProgram(Id);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

GLuint Shader::GetUniformLocation(const GLchar* name)
{
	if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
		return m_uniformLocationCache[name];

	GLCall(GLuint location = glGetUniformLocation(Id, name));
	if (location == -1) std::cout << "Warning: uniform " << name << " doesn't exist!" << std::endl;

	m_uniformLocationCache[name] = location;
	return location;
}

void Shader::SetUniform1f(const GLchar* name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform1i(const GLchar* name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const GLchar* name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const GLchar* name, const glm::mat4& matrix)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix)));
}

GLuint Shader::CompileShader(GLenum type, const std::string source)
{
	GLCall(GLuint id = glCreateShader(type));
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		char message[1024];
		GLCall(glGetShaderInfoLog(id, 1024, nullptr, message));
		std::cout << "Fail to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!" << std::endl;
		std::cout << message << std::endl;
		GLCall(glDeleteShader(id));
		return 0;
	}

	return id;
}
