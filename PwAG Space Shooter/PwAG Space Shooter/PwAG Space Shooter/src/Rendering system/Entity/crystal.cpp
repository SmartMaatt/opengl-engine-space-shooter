#pragma once
#include "pch.h"
#include "entity.h"
#include "crystal.h"
#include <string>

/* --->>> Constructors / Destructor <<<--- */
Crystal::Crystal(GameObject* gameObj, std::string name, float worldRadius) : Entity(gameObj, name)
{
	// Rotation
	setRotation(glm::vec3(-90, 0, 0));

	// Position
	setPosition(Mathf::randCoordsInSphere(worldRadius));
	setOrigin(getPosition()); // For local positioning

	// Scale
	setScale(Mathf::oneVec() * 0.05f);
	setColliderRadius(0.5f);

	// Light
	_light = new Light::Point(getPosition(), { 1,0,0 });
}

Crystal::~Crystal()
{
}

/* --->>> Update <<<--- */
void Crystal::update(float deltaTime)
{
	Entity::update(deltaTime);

	// Rotation
	glm::vec3 newRotation = getRotation() + glm::vec3(0, 0, 6.28f) * deltaTime;
	setRotation(newRotation);
}

/* --->>> Drawing <<<--- */
void Crystal::draw(ShaderProgram* shaderProgram)
{
	Entity::draw(shaderProgram);
}

/* --->>> Destroying <<<--- */
void Crystal::destroy()
{
	delete this;
}

/* --->>> Getters <<<--- */
Light::Point* Crystal::getLight()
{
	return _light;
}
