#pragma once
#include "pch.h"
#include "entity.h"
#include "alien.h"
#include <string>

/* --->>> Constructors / Destructor <<<--- */
Alien::Alien(GameObject* gameObj, std::string name, float worldRadius, float maxReloadTime) : Entity(gameObj, name)
{
	// Position
	float minDistanceFromSpawn = 8;
	glm::vec3 spawnPoint = Mathf::zeroVec();
	do
	{
		spawnPoint = Mathf::randCoordsInSphere(worldRadius);
	} 
	while (glm::distance(spawnPoint, Mathf::zeroVec()) < minDistanceFromSpawn);
	setPosition(spawnPoint);

	// Scale
	float size = 0.2f;
	setScale(glm::vec3(size));
	setColliderRadius(size);

	// Movement
	wanderSpeed = Mathf::randVal(0.4, 0.7);
	attackSpeed = Mathf::randVal(0.7, 1.0);
	setSpeed(wanderSpeed);
	setDirection(glm::vec3(Mathf::randVal(-1.0f, 1.0f), Mathf::randVal(-1.0f, 1.0f), Mathf::randVal(-1.0f, 1.0f)));
	
	// States
	_currentState = AlienState::Wander;
	_attackDistance = 8.0f;

	// Shooting
	_maxReloadTime = maxReloadTime;
}

Alien::~Alien()
{
}

/* --->>> Update <<<--- */
void Alien::update(float deltaTime)
{
	Entity::update(deltaTime);
	float distanceToPlayer = glm::distance(_playerPos, getPosition()); 
	
	// Attack
	if (distanceToPlayer < _attackDistance)
	{
		if (_currentState != AlienState::Attack)
		{
			setSpeed(attackSpeed);
			_reloadTime = _maxReloadTime / 2;
			_readyToShoot = false;
			_currentState = AlienState::Attack;
		}

		if (!_readyToShoot)
		{
			if (_reloadTime < _maxReloadTime)
			{
				_reloadTime += deltaTime;
			}
			else
			{
				_readyToShoot = true;
			}
		}

		glm::vec3 direction = glm::normalize(_playerPos - getPosition());
		setDirection(direction);
		moveWithDirection(deltaTime);
	}

	// Wandering
	else
	{
		// Find new direction
		if (_currentState != AlienState::Wander)
		{
			_readyToShoot = false;
			setSpeed(wanderSpeed);
			setDirection(glm::vec3(Mathf::randVal(-1.0f, 1.0f), Mathf::randVal(-1.0f, 1.0f), Mathf::randVal(-1.0f, 1.0f)));
			_currentState = AlienState::Wander;
		}
		moveWithDirection(deltaTime);
	}
}

void Alien::setPlayerPos(glm::vec3 playerPos)
{
	_playerPos = playerPos;
}


/* --->>> Drawing <<<--- */
void Alien::draw(ShaderProgram* shaderProgram)
{
	glm::vec3 oldPos = getPosition();
	glm::vec3 lookAtRot = lookAt(_direction);
	glm::mat4 rotationMatrix = Mathf::calculateRotationMatrix(lookAtRot);

	setRotation(lookAtRot);
	setPosition(glm::inverse(rotationMatrix) * glm::vec4(oldPos, 0.0f));

	Entity::draw(shaderProgram);
	setRotation(Mathf::zeroVec());
	setPosition(oldPos);
}

glm::vec3 Alien::lookAt(glm::vec3 direction) {
	direction = glm::normalize(direction);
	float yaw = glm::degrees(atan2(direction.x, direction.z));
	//float pitch = glm::degrees(asin(direction.y));

	return glm::vec3(0.0f, yaw, 0.0f);
}

/* --->>> Destroying <<<--- */
void Alien::destroy()
{
	delete this;
}

/* --->>> Collision <<<--- */
void Alien::changeDirectionOnCollision()
{
	glm::vec3 noise = glm::vec3(Mathf::randVal(-0.1f, 0.1f), Mathf::randVal(-0.1f, 0.1f), Mathf::randVal(-0.1f, 0.1f));
	glm::vec3 newDir = getDirection() * glm::vec3(-1) + noise;
	setDirection(glm::clamp(newDir, glm::vec3(-1), glm::vec3(1)));

	glm::vec3 _position = getPosition() + getDirection() * 0.05f;
	setPosition(_position);
}

/* --->>> Shooting <<<--- */
bool Alien::isReadyToShoot()
{
	return _readyToShoot;
}

void Alien::Shoot()
{
	_readyToShoot = false;
	_reloadTime = 0.0f;
}
