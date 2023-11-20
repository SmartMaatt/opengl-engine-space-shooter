#pragma once

class Material
{
public:
	// Constructors / Destructor
	Material();
	Material(Texture* _mainTexture, Texture* specular, Texture* _normalMap, int _diffuseLerp, int _normalLerp, glm::vec3 _ambientLight);
	Material(Material& src);
	virtual ~Material();

	// Setters
	void setTextures(Texture* texture, Texture* specular, Texture* _normalMap);
	void setUniformValues(int _diffuseLerp, int _normalLerp, glm::vec3 _ambientLight);

	// Getters
	int GetDiffuseLerp();
	int GetNormalLerp();
	glm::vec3 GetAmpientLight();

	Texture* GetMainTexture();
	Texture* GetSpecularTexture();
	Texture* GetNormalMap();

	// Drawing
	void bindTextures();
	void setMaterialShaderUniforms(ShaderProgram& shaderProgram);

private:
	// Uniforms
	int _diffuseLerp;
	int _normalLerp;
	glm::vec3 _ambientLight = glm::vec3(0.1f, 0.1f, 0.1f);

	// Textures
	Texture* _mainTexture;
	Texture* _specularTexture;
	Texture* _normalMap;
};