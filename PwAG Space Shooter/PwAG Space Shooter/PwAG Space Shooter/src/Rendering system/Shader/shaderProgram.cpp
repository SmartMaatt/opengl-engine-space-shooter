#include "pch.h"
#include "shaderProgram.h"

/* --->>> Constructors / Destructor <<<--- */
ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept
{
	_shaderProgram = other._shaderProgram;
	other._shaderProgram = 0;

	_uniformLocation.swap(other._uniformLocation);
}

ShaderProgram::~ShaderProgram()
{
	if (_shaderProgram)
	{
		glDeleteProgram(_shaderProgram);
	}
}


/* --->>> Operators <<<--- */
ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept
{
	if (this != &other)
	{
		_shaderProgram = other._shaderProgram;
		other._shaderProgram = 0;

		_uniformLocation.swap(other._uniformLocation);
	}
	return *this;
}


/* --->>> Linking <<<--- */
void ShaderProgram::attachShader(const Shader& shader)
{
	glAttachShader(_shaderProgram, shader.getShaderID());
}

bool ShaderProgram::linkShaderProgram()
{
	glLinkProgram(_shaderProgram);

	int success;
	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		char infoLog[1024];
		glGetProgramInfoLog(_shaderProgram, 512, nullptr, infoLog);
		Debug::LogError(infoLog);

		return false;
	}
	return true;
}


/* --->>> Setters <<<--- */
void ShaderProgram::setInt(const std::string& name, int value) const
{
	const GLint location = _getUniformLocation(name);
	glUniform1i(location, value);
}

void ShaderProgram::setFloat(const std::string& name, float value) const
{
	const GLint location = _getUniformLocation(name);
	glUniform1f(location, value);
}

void ShaderProgram::setVec2f(const std::string& name, const glm::vec2& vector) const
{
	const GLint location = _getUniformLocation(name);
	glUniform2f(location, vector.x, vector.y);
}

void ShaderProgram::setVec3f(const std::string& name, const glm::vec3& vector) const
{
	const GLint location = _getUniformLocation(name);
	glUniform3f(location, vector.x, vector.y, vector.z);
}

void ShaderProgram::setVec4f(const std::string& name, const glm::vec4& vector) const
{
	const GLint location = _getUniformLocation(name);
	glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
}

void ShaderProgram::setMat4(const std::string& name, const glm::mat4& matrix) const
{
	const GLint location = _getUniformLocation(name);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}


/* --->>> Getters <<<--- */
GLint ShaderProgram::_getUniformLocation(const std::string& name) const
{
	if (_uniformLocation.find(name) != _uniformLocation.end())
	{
		return _uniformLocation[name];
	}

	const GLint location = glGetUniformLocation(_shaderProgram, name.c_str());
	_uniformLocation[name] = location;

	return location;
}
