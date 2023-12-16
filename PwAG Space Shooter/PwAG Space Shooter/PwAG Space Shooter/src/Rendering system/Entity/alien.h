#pragma once
#include "entity.h"
#include "../Lighting/point.h"

class Alien : public Entity
{
public:
	// Constructors / Destructor
	Alien(GameObject* gameObj, std::string name, float worldRadius);
	~Alien();

	// Update
	void update(float deltaTime);
	void setPlayerPos(glm::vec3 playerPos);

	// Drawing
	void draw(ShaderProgram* shaderProgram);
	glm::vec3 lookAt(glm::vec3 direction);

	// Destroying
	void destroy();

	// Collision
	void changeDirectionOnCollision();

private:
	enum class AlienState {
		Wander,
		Chase,
		Attack
	};

	AlienState _currentState;
	glm::vec3 _playerPos = glm::vec3(0.0f);
	float _chaseDistance = 3.0f;
	float _attackDistance = 1.0f;
};