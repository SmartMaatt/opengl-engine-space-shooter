#include "pch.h"
#include "material.h"
#include <stdexcept>

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


// Setters
void Material::setTextures(Texture* mainTexture, Texture* specular, Texture* normalMap)
{
	if (mainTexture == nullptr)
	{
		throw std::invalid_argument("MainTexture can't be nullptr!");
		return;
	}

	this->mainTexture = mainTexture;
	this->specularTexture = specular;
	this->normalMap = normalMap;
}

void Material::setUniformValues(int diffuseLerp, int normalLerp, glm::vec3 ambientLight)
{
	this->diffuseLerp = diffuseLerp;
	this->normalLerp = normalLerp;
	this->ambientLight = ambientLight;
}


// Getters
int Material::GetDiffuseLerp()
{
	return this->diffuseLerp;
}

int Material::GetNormalLerp()
{
	return this->normalLerp;
}

glm::vec3 Material::GetAmpientLight()
{
	return this->ambientLight;
}

Texture* Material::GetMainTexture()
{
	return this->mainTexture;
}

Texture* Material::GetSpecularTexture()
{
	return this->specularTexture;
}

Texture* Material::GetNormalMap()
{
	return this->normalMap;
}


// Drawing methods
void Material::bindTextures()
{
	this->mainTexture->bindTexture(0);
	if (this->specularTexture)
	{
		this->specularTexture->bindTexture(1);
	}

	if (this->normalMap)
	{
		this->normalMap->bindTexture(2);
	}
}

void Material::setMaterialShaderUniforms(ShaderProgram& shaderProgram)
{
	shaderProgram.setInt("diffuse", 0);
	shaderProgram.setInt("normalMap", 1);
	shaderProgram.setVec3f("ambientLight", this->ambientLight);
}

Material::~Material()
{
}