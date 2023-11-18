#include "pch.h"
#include "gameObject.h"

GameObject::GameObject() 
{

}

GameObject::GameObject(Material* material, Mesh* mesh) 
{
	this->material = material;
	this->mesh = mesh;
}

void GameObject::draw(ShaderProgram* shaderProgram) 
{
	// Use shader
	shaderProgram->useShader();

	// Binding textures
	this->material->bindTextures();

	// Setting uniforms
	this->mesh->setMeshUniform(shaderProgram);
	this->material->setMaterialShaderUniforms(*shaderProgram);

	this->mesh->setMatrixModel(
		this->transformation.objectPosition,
		this->transformation.objectOrigin,
		this->transformation.objectRotation,
		this->transformation.objectScale);

	// Shader per vertex values
	this->mesh->drawMesh();
}

void GameObject::setPosition(const glm::vec3 position)
{
	this->transformation.objectPosition = position;
}

void GameObject::setOrigin(const glm::vec3 origin)
{
	this->transformation.objectOrigin = origin;
}

void GameObject::setRotation(const glm::vec3 rotation)
{
	this->transformation.objectRotation = rotation;
}

void GameObject::setScale(const glm::vec3 scale)
{
	this->transformation.objectScale = scale;
}

glm::vec3 GameObject::getPosition() 
{
	return this->transformation.objectPosition;
}

glm::vec3 GameObject::getRotation() {
	return this->transformation.objectRotation;
}

GameObject::~GameObject()
{
	if (this->material)
	{
		delete this->material;
		this->material = nullptr;
	}

	if (this->mesh)
	{
		delete this->mesh;
		this->mesh = nullptr;
	}
}