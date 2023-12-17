#pragma once
#include "pch.h"
#include "livingEntity.h"
#include "bullet.h"
#include <string>

/* --->>> Constructors / Destructor <<<--- */
Bullet::Bullet(GameObject* gameObj, std::string name, float lifeSpan, glm::vec3 position, glm::vec3 direction, glm::vec3 lightColor) : LivingEntity(gameObj, name, lifeSpan)
{
	// Position
	setPosition(position + direction * 0.5f);
	setOrigin(position);

	// Scale
	setScale(Mathf::oneVec() * 0.05f);
	setColliderRadius(0.5f);

	// Movement
	setDirection(direction);
	setSpeed(5);

	// Light
	_light = new Light::Point(getPosition(), lightColor);
}

Bullet::~Bullet()
{
}

/* --->>> Update <<<--- */
void Bullet::update(float deltaTime)
{
	LivingEntity::update(deltaTime);

	moveWithDirection(deltaTime);
	_light->setPosition(getPosition());
}

/* --->>> Drawing <<<--- */
void Bullet::draw(ShaderProgram* shaderProgram)
{
	LivingEntity::draw(shaderProgram);
}

/* --->>> Destroying <<<--- */
void Bullet::destroy()
{
	delete this;
}

/* --->>> Getters <<<--- */
Light::Point* Bullet::getLight()
{
	return _light;
}
