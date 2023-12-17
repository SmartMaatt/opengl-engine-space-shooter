#pragma once
#include "pch.h"
#include "entity.h"
#include "medkit.h"
#include <string>

/* --->>> Constructors / Destructor <<<--- */
Medkit::Medkit(GameObject* gameObj, std::string name, float worldRadius) : Entity(gameObj, name)
{
	// Position
	setPosition(Mathf::randCoordsInSphere(worldRadius));
	setOrigin(getPosition()); // For local positioning

	// Scale
	setScale(Mathf::oneVec() * 0.2f);
	setColliderRadius(0.5f);

	// Light
	_light = new Light::Point(getPosition(), { 1,0,0 });
}

Medkit::~Medkit()
{
}

/* --->>> Update <<<--- */
void Medkit::update(float deltaTime)
{
	Entity::update(deltaTime);

	// Rotation
	glm::vec3 newRotation = getRotation() + glm::vec3(0, 6.28f, 0) * deltaTime;
	setRotation(newRotation);
}

/* --->>> Drawing <<<--- */
void Medkit::draw(ShaderProgram* shaderProgram)
{
	Entity::draw(shaderProgram);
}

/* --->>> Destroying <<<--- */
void Medkit::destroy()
{
	delete this;
}

/* --->>> Getters <<<--- */
Light::Point* Medkit::getLight()
{
	return _light;
}
