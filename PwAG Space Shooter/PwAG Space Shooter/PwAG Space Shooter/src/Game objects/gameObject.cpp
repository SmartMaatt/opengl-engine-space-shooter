#include "pch.h"
#include "gameObject.h"

GameObject::GameObject() 
{

}

GameObject::GameObject(Material* material, Texture* texture, IndexedDataOBJ objData, glm::vec3 offset, int instances) 
{
	this->material = material;
	this->texture = texture;

	this->mesh = new Mesh(objData, offset, instances);
}

void GameObject::draw(ShaderProgram* shaderProgram) 
{
	// Use shader
	shaderProgram->useShader();

	// Textures
	this->texture->bindTexture(0);
	if (this->specular)
	{
		this->specular->bindTexture(1);
	}

	if (this->normalMapTexture != nullptr) 
	{
		this->normalMapTexture->bindTexture(2);
	}

	// Shader uniform values
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

void GameObject::setNormalMapTexture(Texture* normalMapTexture)
{
	this->normalMapTexture = normalMapTexture;
}

void GameObject::setTexture(Texture* texture)
{
	this->texture = texture;
}

void GameObject::setSpecular(Texture* texture)
{
	this->specular = texture;
}

glm::vec3 GameObject::getPosition() {
	return this->transformation.objectPosition;
}

glm::vec3 GameObject::getRotation() {
	return this->transformation.objectRotation;
}

GameObject::~GameObject()
{
	delete this->mesh;

	if (this->normalMapTexture != nullptr) 
	{
		delete this->normalMapTexture;
	}
}