#pragma once
#include "pch.h"
#include "entity.h"
#include "alien.h"
#include <string>

/* --->>> Constructors / Destructor <<<--- */
Alien::Alien(GameObject* gameObj, std::string name, float worldRadius) : Entity(gameObj, name)
{
	// Position
	//setPosition(Mathf::randCoordsInSphere(worldRadius));
	setPosition(Mathf::zeroVec());

	// Scale
	float size = 0.2f;
	setScale(glm::vec3(size));
	setColliderRadius(size);

	// Movement
	setSpeed(0.5f);
	setDirection(glm::vec3(Mathf::randVal(-1.0f, 1.0f), Mathf::randVal(-1.0f, 1.0f), Mathf::randVal(-1.0f, 1.0f)));
	
	// States
	_currentState = AlienState::Wander;
	_chaseDistance = 5.0f;
	_attackDistance = 2.0f;
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
		_currentState = AlienState::Attack;
		// Attack TO DO
	}

	// Chase
	else if (distanceToPlayer < _chaseDistance)
	{
		if (_currentState != AlienState::Chase)
		{
			setSpeed(1);
			_currentState = AlienState::Chase;
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
			setDirection(glm::vec3(Mathf::randVal(-1.0f, 1.0f), Mathf::randVal(-1.0f, 1.0f), Mathf::randVal(-1.0f, 1.0f)));
			setSpeed(0.5f);
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