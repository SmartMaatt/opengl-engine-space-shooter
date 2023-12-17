#pragma once
#include "entity.h"
#include "../Lighting/point.h"

class Alien : public Entity
{
public:
	// Constructors / Destructor
	Alien(GameObject* gameObj, std::string name, float worldRadius, float maxReloadTime);
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

	// Shooting
	bool isReadyToShoot();
	void Shoot();

private:
	enum class AlienState {
		Wander,
		Attack
	};

	// Parameters
	AlienState _currentState;
	glm::vec3 _playerPos = glm::vec3(0.0f);
	float _attackDistance = 5.0f;

	// Speed
	float wanderSpeed = 0.25f;
	float attackSpeed = 0.5f;

	// Shooting
	float _maxReloadTime = 0.5f;
	float _reloadTime = 0.0f;
	bool _readyToShoot = false;
};