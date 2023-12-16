#pragma once
#include "../Rendering system/Model/gameObject.h"

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
	glm::vec3 lookAt(glm::vec3 direction);

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
	// References
	GameObject* _gameObj = nullptr;

	// Parameters
	std::string _name = "";
	glm::vec3 _direction = glm::vec3(0.0f);
	float _speed = 0;
	float _colRad = 0;
};