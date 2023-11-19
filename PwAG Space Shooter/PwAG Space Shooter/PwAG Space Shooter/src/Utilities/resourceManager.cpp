#include "pch.h"
#include "resourceManager.h"

/* --->>> Instance <<<--- */
ResourceManager ResourceManager::_instance;


/* --->>> Texture <<<--- */
void ResourceManager::loadTexture(const std::string& resourceName, const std::string& textureFilePath, Texture::Type type)
{
	_textures.insert(std::make_pair(resourceName, Texture::createTextureFromFile(textureFilePath, type)));
}

const Texture& ResourceManager::getTexture(const std::string& resourceName) const
{
	return _textures.at(resourceName);
}


/* --->>> Font <<<--- */
void ResourceManager::loadFont(const std::string& resourceName, const std::string& fontFilePath, uint32_t size)
{
	_fonts.insert(std::make_pair(resourceName, Font(fontFilePath, size)));
}

const Font& ResourceManager::getFont(const std::string& resourceName)
{
	return _fonts.at(resourceName);
}


/* --->>> Shader <<<--- */
void ResourceManager::addShaderProgram(const std::string& resourceName, const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
{
	Shader vert = Shader::createShaderFromFile(vertexShaderFilePath, Shader::Type::eVertex);
	Shader frag = Shader::createShaderFromFile(fragmentShaderFilePath, Shader::Type::eFragment);

	ShaderProgram program;
	program.attachShader(vert);
	program.attachShader(frag);
	program.linkShaderProgram();

	_shaders.insert(std::make_pair(resourceName, std::move(program)));
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

	_shaders.insert(std::make_pair(resourceName, std::move(program)));
}

const ShaderProgram& ResourceManager::getShader(const std::string& resourceName)
{
	return _shaders.at(resourceName);
}
