#pragma once
#include "pch.h"
#include "entity.h"
#include "meteor.h"
#include <string>

/* --->>> Constructors / Destructor <<<--- */
Meteor::Meteor(GameObject* gameObj, std::string name, float worldRadius) : Entity(gameObj, name)
{
	// Position
	float minDistanceFromSpawn = 5;
	glm::vec3 spawnPoint = Mathf::zeroVec();
	do
	{
		spawnPoint = Mathf::randCoordsInSphere(worldRadius);
	} 
	while (glm::distance(spawnPoint, Mathf::zeroVec()) < minDistanceFromSpawn);
	setPosition(spawnPoint);

	// Scale
	float size = Mathf::randVal(0.1f, 0.75f);
	//float size = 0.01f;
	setScale(glm::vec3(size, size, size));
	setColliderRadius(size);

	// Movement
	setDirection(glm::vec3(Mathf::randVal(-1.0f, 1.0f), Mathf::randVal(-1.0f, 1.0f), Mathf::randVal(-1.0f, 1.0f)));
	setSpeed(Mathf::randVal(0.3f, 0.7f));
}

Meteor::~Meteor()
{
}

/* --->>> Update <<<--- */
void Meteor::update(float deltaTime)
{
	Entity::update(deltaTime);

	// Move
	moveWithDirection(deltaTime);
}

/* --->>> Drawing <<<--- */
void Meteor::draw(ShaderProgram* shaderProgram)
{
	Entity::draw(shaderProgram);
}

/* --->>> Destroying <<<--- */
void Meteor::destroy()
{
	delete this;
}

/* --->>> Collision <<<--- */
void Meteor::changeDirectionOnCollision()
{
	glm::vec3 noise = glm::vec3(Mathf::randVal(-0.1f, 0.1f), Mathf::randVal(-0.1f, 0.1f), Mathf::randVal(-0.1f, 0.1f));
	glm::vec3 newDir = getDirection() * glm::vec3(-1) + noise;
	setDirection(glm::clamp(newDir, glm::vec3(-1), glm::vec3(1)));

	glm::vec3 _position = getPosition() + getDirection() * 0.05f;
	setPosition(_position);
}