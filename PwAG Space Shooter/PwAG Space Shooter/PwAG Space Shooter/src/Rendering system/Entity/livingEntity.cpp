#pragma once
#include "pch.h"
#include "entity.h"
#include "livingEntity.h"
#include <string>

/* --->>> Constructors / Destructor <<<--- */
LivingEntity::LivingEntity(GameObject* gameObj, std::string name, float lifeSpan) : Entity(gameObj, name)
{
	_lifeSpan = lifeSpan;
}

LivingEntity::~LivingEntity()
{
}

/* --->>> Update <<<--- */
void LivingEntity::update(float deltaTime)
{
	Entity::update(deltaTime);

	// Aging
	_calcAge(deltaTime);
	if (isDead())
	{
		Debug::Log("Object " + _name + " aged to death!");
		// Has to be killed by external manager
	}
}

/* --->>> Drawing <<<--- */
void LivingEntity::draw(ShaderProgram* shaderProgram)
{
	Entity::draw(shaderProgram);
}

/* --->>> Destroying <<<--- */
void LivingEntity::destroy()
{
	delete this;
}

/* --->>> Life span <<<--- */
bool LivingEntity::isDead()
{
	return _dead;
}

float LivingEntity::getAge()
{
	return _age;
}

void LivingEntity::_calcAge(float deltaTime)
{
	_age += deltaTime;
	_dead = _age > _lifeSpan;
}