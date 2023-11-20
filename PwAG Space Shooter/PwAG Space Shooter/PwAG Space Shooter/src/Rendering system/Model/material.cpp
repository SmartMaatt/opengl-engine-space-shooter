#include "pch.h"
#include "material.h"
#include <stdexcept>

/* --->>> Constructors / Destructor <<<--- */
Material::Material() 
{
}

Material::Material(Texture* mainTexture, Texture* specular, Texture* normalMap, int diffuseLerp, int normalLerp, glm::vec3 ambientLight)
{
	setTextures(mainTexture, specular, normalMap);
	setUniformValues(diffuseLerp, normalLerp, ambientLight);
}

Material::Material(Material& src)
{
	setTextures(src.GetMainTexture(), src.GetSpecularTexture(), src.GetNormalMap());
	setUniformValues(src.GetDiffuseLerp(), src.GetNormalLerp(), src.GetAmpientLight());
}

Material::~Material()
{
}


/* --->>> Setters <<<--- */
void Material::setTextures(Texture* mainTexture, Texture* specular, Texture* normalMap)
{
	if (mainTexture == nullptr)
	{
		throw std::invalid_argument("MainTexture can't be nullptr!");
		return;
	}

	_mainTexture = mainTexture;
	_specularTexture = specular;
	_normalMap = normalMap;
}

void Material::setUniformValues(int diffuseLerp, int normalLerp, glm::vec3 ambientLight)
{
	_diffuseLerp = diffuseLerp;
	_normalLerp = normalLerp;
	_ambientLight = ambientLight;
}


/* --->>> Getters <<<--- */
int Material::GetDiffuseLerp()
{
	return _diffuseLerp;
}

int Material::GetNormalLerp()
{
	return _normalLerp;
}

glm::vec3 Material::GetAmpientLight()
{
	return _ambientLight;
}

Texture* Material::GetMainTexture()
{
	return _mainTexture;
}

Texture* Material::GetSpecularTexture()
{
	return _specularTexture;
}

Texture* Material::GetNormalMap()
{
	return _normalMap;
}


/* --->>> Drawing <<<--- */
void Material::bindTextures()
{
	_mainTexture->bindTexture(0);
	if (_specularTexture)
	{
		_specularTexture->bindTexture(1);
	}

	if (_normalMap)
	{
		_normalMap->bindTexture(2);
	}
}

void Material::setMaterialShaderUniforms(ShaderProgram& shaderProgram)
{
	shaderProgram.setInt("diffuse", 0);
	shaderProgram.setInt("normalMap", 1);
	shaderProgram.setVec3f("ambientLight", _ambientLight);
}