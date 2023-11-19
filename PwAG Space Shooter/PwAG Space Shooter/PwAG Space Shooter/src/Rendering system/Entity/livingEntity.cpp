#pragma once
#include "pch.h"
#include "entity.h"
#include "livingEntity.h"
#include <string>

// Constructors / Destructor
LivingEntity::LivingEntity(GameObject* gameObj, std::string name, float lifeSpan) : Entity(gameObj, name)
{
	this->lifeSpan = lifeSpan;
}

LivingEntity::~LivingEntity()
{
}

// Update
void LivingEntity::update(float deltaTime)
{
	Entity::update(deltaTime);

	// Aging
	calcAge(deltaTime);
	if (isDead())
	{
		Debug::Log("Object " + name + " aged to death!");
		// Has to be killed by external manager
	}
}

// Drawing
void LivingEntity::draw(ShaderProgram* shaderProgram)
{
	Entity::draw(shaderProgram);
}

// Destroying;
void LivingEntity::destroy()
{
	delete this;
}

// Life span
bool LivingEntity::isDead()
{
	return this->dead;
}

void LivingEntity::calcAge(float deltaTime)
{
	age += deltaTime;
	dead = age > lifeSpan;
}