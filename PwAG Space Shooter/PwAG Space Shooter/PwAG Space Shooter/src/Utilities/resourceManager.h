#pragma once
#include "../Rendering system/Texture/texture.h"
#include "../Rendering system/Text/font.h"

//singleton
class ResourceManager
{
public:
	static ResourceManager& getInstance()
	{
		return _instance;
	}

	// Constructors / Destructor
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	// Texture
	void loadTexture(const std::string& resourceName, const std::string& textureFilePath, Texture::Type type);
	const Texture& getTexture(const std::string& resourceName) const;

	// Font
	void loadFont(const std::string& resourceName, const std::string& fontFilePath, uint32_t size);
	const Font& getFont(const std::string& resourceName);

	// Shader
	void addShaderProgram(const std::string& resourceName, const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
	void addShaderProgram(const std::string& resourceName, const std::string& vertexShaderFilePath, const std::string& geometryShaderFilePath, const std::string& fragmentShaderFilePath);
	const ShaderProgram& getShader(const std::string& resourceName);

private:
	ResourceManager() = default;
	static ResourceManager _instance;

	std::unordered_map<std::string, Texture> _textures;
	std::unordered_map<std::string, Font> _fonts;
	std::unordered_map<std::string, ShaderProgram> _shaders;
};

