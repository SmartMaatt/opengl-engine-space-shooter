#pragma once
#include "../Rendering system/Texture/texture.h"
#include "../Rendering system/Model/material.h"
#include "../Rendering system/Model/mesh.h"
#include "../Rendering system/Model/transformationOBJ.h"
#include "../Rendering system/Model/indexedDataOBJ.h"

class GameObject
{
public:
	// Constructors / Destructor
	GameObject();
	GameObject(Material* material, Mesh* mesh);
	~GameObject();

	// Drawing
	void draw(ShaderProgram* shaderProgram);

	// Getters / Setters
	void setPosition(const glm::vec3 _position);
	void setOrigin(const glm::vec3 origin);
	void setRotation(const glm::vec3 rotation);
	void setScale(const glm::vec3 scale);

	glm::vec3 getPosition();
	glm::vec3 getRotation();

private:
	TransformationOBJ _transformation;
	Material* _material;
	Mesh* _mesh;
};