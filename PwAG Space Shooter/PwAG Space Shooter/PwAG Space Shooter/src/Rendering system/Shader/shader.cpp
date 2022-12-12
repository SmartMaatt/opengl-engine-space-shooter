#include "pch.h"
#include "shader.h"

Shader::Shader(Type type)
	: type(type)
{
	switch (type)
	{
	case Shader::Type::eVertex:
		shaderID = glCreateShader(GL_VERTEX_SHADER);
		break;
	case Shader::Type::eFragment:
		shaderID = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	case Shader::Type::eGeometry:
		shaderID = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	}
}

Shader::Shader(Shader&& other) noexcept
	: type(other.type)
{
	this->shaderID = other.shaderID;
	other.shaderID = 0;
}

Shader::~Shader()
{
	if (shaderID)
	{
		glDeleteShader(shaderID);
	}
}

Shader& Shader::operator=(Shader&& other) noexcept
{
	if (this != &other)
	{
		this->type = other.type;

		this->shaderID = other.shaderID;
		other.shaderID = 0;
	}

	return *this;
}

Shader Shader::createShaderFromSourceCode(const std::string& sourceCode, Type type)
{
	Shader shader{ type };
	shader.setSourceCode(sourceCode);
	shader.compile();

	return shader;
}

Shader Shader::createShaderFromFile(const std::string& filePath, Type type)
{
	Shader shader{ type };

	std::string sourceCode = loadShaderSourceCodeFromFile(filePath);
	shader.setSourceCode(sourceCode);
	shader.compile();

	return shader;
}

std::string Shader::loadShaderSourceCodeFromFile(const std::string& filePath)
{
	std::ifstream file(filePath);
	if (file.is_open())
	{
		file.seekg(0, std::ios::end);

		size_t size = file.tellg();
		std::string buffer(size, ' ');

		file.seekg(0);
		file.read(&buffer[0], size);

		file.close();
		return buffer;
	}

	return std::string();
}

void Shader::setSourceCode(const std::string& sourceCode)
{
	const char* code = sourceCode.c_str();
	glShaderSource(shaderID, 1, &code, nullptr);
}

void Shader::compile()
{
	glCompileShader(this->shaderID);

	int success;
	glGetShaderiv(this->shaderID, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		char infoLog[1024];
		glGetShaderInfoLog(this->shaderID, 512, nullptr, infoLog);
		std::cout << infoLog << std::endl;
		//TODO - some exception?
	}
}
