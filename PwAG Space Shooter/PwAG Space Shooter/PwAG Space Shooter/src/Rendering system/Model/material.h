#pragma once

class Material
{
public:
	Material();
	Material(Texture* mainTexture, Texture* specular, Texture* normalMap, int diffuseLerp, int normalLerp, glm::vec3 ambientLight);
	Material(Material& src);

	// Setters
	void setTextures(Texture* texture, Texture* specular, Texture* normalMap);
	void setUniformValues(int diffuseLerp, int normalLerp, glm::vec3 ambientLight);

	// Getters
	int GetDiffuseLerp();
	int GetNormalLerp();
	glm::vec3 GetAmpientLight();

	Texture* GetMainTexture();
	Texture* GetSpecularTexture();
	Texture* GetNormalMap();

	// Drawing methods
	void bindTextures();
	void setMaterialShaderUniforms(ShaderProgram& shaderProgram);

	virtual ~Material();

private:
	// Uniforms
	int diffuseLerp;
	int normalLerp;
	glm::vec3 ambientLight = glm::vec3(0.1f, 0.1f, 0.1f);

	// Textures
	Texture* mainTexture;
	Texture* specularTexture;
	Texture* normalMap;
};