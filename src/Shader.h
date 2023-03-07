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

	void Bind() const;
	void Unbind() const;

	void Delete() const;

	GLuint GetUniformLocation(std::string name);

	void SetUniform1f(std::string name, float value);
	void SetUniform1i(std::string name, int value);
	void SetUniform3f(std::string name, float v0, float v1, float v2);
	void SetUniform4f(std::string name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(std::string name, const glm::mat4& matrix);

private:
	// Properties
	std::unordered_map<std::string, GLuint> m_uniformLocationCache;


	// Method
	static GLuint CompileShader(GLenum type, const std::string source);
};

