#include "pch.h"
#include "material.h"

Material::Material() {

}

Material::Material(glm::vec3 ambientLight) {
	this->ambientLight = ambientLight;
}

void Material::setMaterialShaderUniforms(ShaderProgram& shaderProgram) {
	shaderProgram.setInt("diffuse", 0);
	shaderProgram.setInt("normalMap", 1);

	shaderProgram.setVec3f("ambientLight", this->ambientLight);
}

Material::~Material()
{

}