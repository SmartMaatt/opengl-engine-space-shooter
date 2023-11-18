#pragma once
#include "../../Game objects/gameObject.h"

class Entity 
{
public:
	// Constructors / Destructor
	Entity(GameObject* gameObj, std::string name);
	~Entity();

	// Update
	void update(float deltaTime);

	// Drawing
	void draw(ShaderProgram* shaderProgram);

	// Destroying;
	void destroy();

	// Naming
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

	// Collision
	void setColliderRadius(float colRad);
	float getColliderRadius();

protected:
	GameObject* gameObj = nullptr;
	std::string name = "";
	glm::vec3 direction = glm::vec3(0.0f);

	float speed = 0;
	float colRad = 0;
};