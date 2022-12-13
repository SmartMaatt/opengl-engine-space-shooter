#pragma once
#include "../../Game objects/gameObject.h"

class Entity 
{
public:
	Entity(GameObject* model);
	~Entity();

	void drawEntity(ShaderProgram* shaderProgram);

	// Name
	void setName(std::string name);
	std::string getName();

	// Position
	void setPosition(const glm::vec3 position);
	glm::vec3 getPosition();
	void setOrigin(const glm::vec3 origin);

	// Rotation
	void setRotation(const glm::vec3 rotation);
	glm::vec3 getRotation();

	// Scale
	void setScale(const glm::vec3 scale);

	// Direction
	void setDirection(glm::vec3 direction);
	glm::vec3 getDirection();
	void moveWithDirection(float deltaTime);

	// Speed
	void setSpeed(float speed);
	float getSpeed();

	// Collider radius
	void setColliderRadius(float colRad);
	float getColliderRadius();

protected:
	std::string name;
	GameObject* model;
	glm::vec3 direction = glm::vec3(0.0f);
	float speed = 0;
	float colRad = 0;
};