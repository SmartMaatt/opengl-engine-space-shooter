#include "pch.h"
#include "resourceManager.h"

ResourceManager ResourceManager::instance;

void ResourceManager::loadTexture(const std::string& resourceName, const std::string& textureFilePath, Texture::Type type)
{
	textures.insert(std::make_pair(resourceName, Texture::createTextureFromFile(textureFilePath, type)));
}

void ResourceManager::loadFont(const std::string& resourceName, const std::string& fontFilePath, uint32_t size)
{
	fonts.insert(std::make_pair(resourceName, Font(fontFilePath, size)));
}

void ResourceManager::addShaderProgram(const std::string& resourceName, const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
{
	Shader vert = Shader::createShaderFromFile(vertexShaderFilePath, Shader::Type::eVertex);
	Shader frag = Shader::createShaderFromFile(fragmentShaderFilePath, Shader::Type::eFragment);

	ShaderProgram program;
	program.attachShader(vert);
	program.attachShader(frag);
	program.linkShaderProgram();

	this->shaders.insert(std::make_pair(resourceName, std::move(program)));
}

void ResourceManager::addShaderProgram(const std::string& resourceName, const std::string& vertexShaderFilePath, const std::string& geometryShaderFilePath, const std::string& fragmentShaderFilePath)
{
	Shader vert = Shader::createShaderFromFile(vertexShaderFilePath, Shader::Type::eVertex);
	Shader geom = Shader::createShaderFromFile(geometryShaderFilePath, Shader::Type::eGeometry);
	Shader frag = Shader::createShaderFromFile(fragmentShaderFilePath, Shader::Type::eFragment);

	ShaderProgram program;
	program.attachShader(vert);
	program.attachShader(geom);
	program.attachShader(frag);
	program.linkShaderProgram();

	this->shaders.insert(std::make_pair(resourceName, std::move(program)));
}
