#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include <unordered_map>

class Shader
{
public:
	// Properties
	GLuint Id;


	// Method
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	GLuint GetUniformLocation(const GLchar* name);

	void SetUniform1f(const GLchar* name, float value);
	void SetUniform1i(const GLchar* name, int value);
	void SetUniform3f(const GLchar* name, float v0, float v1, float v2);
	void SetUniform4f(const GLchar* name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const GLchar* name, const glm::mat4& matrix);

private:
	// Properties
	std::unordered_map<const GLchar*, GLuint> m_uniformLocationCache;


	// Method
	static GLuint CompileShader(GLenum type, const std::string source);
};

