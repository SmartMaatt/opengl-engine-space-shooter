#include "pch.h"
#include "shader.h"

/* --->>> Constructors / Destructor <<<--- */
Shader::Shader(Type type) : _type(type)
{
	switch (type)
	{
	case Shader::Type::eVertex:
		_shaderID = glCreateShader(GL_VERTEX_SHADER);
		break;
	case Shader::Type::eFragment:
		_shaderID = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	case Shader::Type::eGeometry:
		_shaderID = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	}
}

Shader::Shader(Shader&& other) noexcept
	: _type(other._type)
{
	_shaderID = other._shaderID;
	other._shaderID = 0;
}

Shader::~Shader()
{
	if (_shaderID)
	{
		glDeleteShader(_shaderID);
	}
}


/* --->>> Operators <<<--- */
Shader& Shader::operator=(Shader&& other) noexcept
{
	if (this != &other)
	{
		_type = other._type;

		_shaderID = other._shaderID;
		other._shaderID = 0;
	}

	return *this;
}


/* --->>> Initialization <<<--- */
Shader Shader::createShaderFromSourceCode(const std::string& sourceCode, Type type)
{
	Shader shader{ type };
	shader._setSourceCode(sourceCode);
	shader._compile();

	return shader;
}

Shader Shader::createShaderFromFile(const std::string& filePath, Type type)
{
	Shader shader{ type };

	std::string sourceCode = _loadShaderSourceCodeFromFile(filePath);
	shader._setSourceCode(sourceCode);
	shader._compile();

	return shader;
}


/* --->>> Private <<<--- */
std::string Shader::_loadShaderSourceCodeFromFile(const std::string& filePath)
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

void Shader::_setSourceCode(const std::string& sourceCode)
{
	const char* code = sourceCode.c_str();
	glShaderSource(_shaderID, 1, &code, nullptr);
}

void Shader::_compile()
{
	glCompileShader(_shaderID);

	int success;
	glGetShaderiv(_shaderID, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		char infoLog[1024];
		glGetShaderInfoLog(_shaderID, 512, nullptr, infoLog);
		Debug::LogError(infoLog);
		//TODO - some exception?
	}
}
