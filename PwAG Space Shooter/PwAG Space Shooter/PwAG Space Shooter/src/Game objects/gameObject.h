#pragma once
#include "../Rendering system/Texture/texture.h"
#include "../Rendering system/Model/material.h"
#include "../Rendering system/Model/mesh.h"
#include "../Rendering system/Model/transformationOBJ.h"
#include "../Rendering system/Model/indexedDataOBJ.h"

class GameObject
{
public:
	GameObject();
	GameObject(Material* material, Texture* texture, IndexedDataOBJ objData, glm::vec3 offset, int instances);

	void draw(ShaderProgram* shaderProgram);

	void setPosition(const glm::vec3 position);
	void setOrigin(const glm::vec3 origin);
	void setRotation(const glm::vec3 rotation);
	void setScale(const glm::vec3 scale);

	void setNormalMapTexture(Texture* normalMapTexture);

	void setTexture(Texture* texture);
	void setSpecular(Texture* texture);

	glm::vec3 getPosition();
	glm::vec3 getRotation();

	~GameObject();

private:
	TransformationOBJ transformation;

	Texture* texture;
	Texture* specular;
	Texture* normalMapTexture;

	Material* material;
	Mesh* mesh;
};