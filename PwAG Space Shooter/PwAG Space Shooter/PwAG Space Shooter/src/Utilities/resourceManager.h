#pragma once
#include "../Rendering system/Texture/texture.h"
#include "../Rendering system/Text/font.h"

//singleton
class ResourceManager
{
public:
	static ResourceManager& getInstance()
	{
		return instance;
	}
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	void loadTexture(const std::string& resourceName, const std::string& textureFilePath, Texture::Type type);
	const Texture& getTexture(const std::string& resourceName) const
	{
		return textures.at(resourceName);
	}

	void loadFont(const std::string& resourceName, const std::string& fontFilePath, uint32_t size);
	const Font& getFont(const std::string& resourceName)
	{
		return fonts.at(resourceName);
	}

	void addShaderProgram(const std::string& resourceName, const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
	void addShaderProgram(const std::string& resourceName, const std::string& vertexShaderFilePath, const std::string& geometryShaderFilePath, const std::string& fragmentShaderFilePath);
	const ShaderProgram& getShader(const std::string& resourceName)
	{
		return shaders.at(resourceName);
	}
private:
	ResourceManager() = default;
	static ResourceManager instance;

	std::unordered_map<std::string, Texture> textures;
	std::unordered_map<std::string, Font> fonts;
	std::unordered_map<std::string, ShaderProgram> shaders;
};

