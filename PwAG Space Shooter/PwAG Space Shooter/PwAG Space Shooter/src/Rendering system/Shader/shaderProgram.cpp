#include "pch.h"
#include "shaderProgram.h"

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept
{
	shaderProgram = other.shaderProgram;
	other.shaderProgram = 0;

	uniformLocation.swap(other.uniformLocation);
}

ShaderProgram::~ShaderProgram()
{
	if (shaderProgram)
	{
		glDeleteProgram(shaderProgram);
	}
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept
{
	if (this != &other)
	{
		shaderProgram = other.shaderProgram;
		other.shaderProgram = 0;

		uniformLocation.swap(other.uniformLocation);
	}

	return *this;
}

void ShaderProgram::setInt(const std::string& name, int value) const
{
	const GLint location = getUniformLocation(name);
	glUniform1i(location, value);
}

void ShaderProgram::setFloat(const std::string& name, float value) const
{
	const GLint location = getUniformLocation(name);
	glUniform1f(location, value);
}

void ShaderProgram::setVec2f(const std::string& name, const glm::vec2& vector) const
{
	const GLint location = getUniformLocation(name);
	glUniform2f(location, vector.x, vector.y);
}

void ShaderProgram::setVec3f(const std::string& name, const glm::vec3& vector) const
{
	const GLint location = getUniformLocation(name);
	glUniform3f(location, vector.x, vector.y, vector.z);
}

void ShaderProgram::setVec4f(const std::string& name, const glm::vec4& vector) const
{
	const GLint location = getUniformLocation(name);
	glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
}

void ShaderProgram::setMat4(const std::string& name, const glm::mat4& matrix) const
{
	const GLint location = getUniformLocation(name);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::attachShader(const Shader& shader)
{
	glAttachShader(shaderProgram, shader.getShaderID());
}

bool ShaderProgram::linkShaderProgram()
{
	glLinkProgram(shaderProgram);

	int success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		char infoLog[1024];
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		std::cout << infoLog << std::endl;

		return false;
	}
	return true;
}

GLint ShaderProgram::getUniformLocation(const std::string& name) const
{
	if (uniformLocation.find(name) != uniformLocation.end())
	{
		return uniformLocation[name];
	}

	const GLint location = glGetUniformLocation(shaderProgram, name.c_str());
	uniformLocation[name] = location;

	return location;
}
