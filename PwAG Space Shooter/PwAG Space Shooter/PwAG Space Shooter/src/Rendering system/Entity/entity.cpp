#pragma once
#include "pch.h"
#include "entity.h"
#include <string>

// Constructors / Destructor
Entity::Entity(GameObject* gameObj, std::string name)
{
	this->gameObj = gameObj;
	setName(name);
}

Entity::~Entity()
{
	delete this->gameObj;
}


// Update
void Entity::update(float deltaTime)
{
}


// Drawing
void Entity::draw(ShaderProgram* shaderProgram)
{
	this->gameObj->draw(shaderProgram);
}


// Destroying
void Entity::destroy()
{
	delete this;
}


// Naming
void Entity::setName(std::string name)
{
	this->name = name;
}

std::string Entity::getName()
{
	return this->name;
}


// Position
void Entity::setPosition(const glm::vec3 position)
{
	this->gameObj->setPosition(position);
}

glm::vec3 Entity::getPosition()
{
	return this->gameObj->getPosition();
}

void Entity::setOrigin(const glm::vec3 origin)
{
	this->gameObj->setOrigin(origin);
}


// Rotation
void Entity::setRotation(const glm::vec3 rotation)
{
	this->gameObj->setRotation(rotation);
}

glm::vec3 Entity::getRotation()
{
	return this->gameObj->getRotation();
}


// Scale
void Entity::setScale(const glm::vec3 scale)
{
	this->gameObj->setScale(scale);
}


// Direction
void Entity::setDirection(glm::vec3 direction)
{
	this->direction = direction;
}

glm::vec3 Entity::getDirection()
{
	return this->direction;
}

void Entity::moveWithDirection(float deltaTime)
{
	glm::vec3 newPosition = getPosition() + (deltaTime * speed * direction);
	setPosition(newPosition);
}


// Speed
void Entity::setSpeed(float speed)
{
	this->speed = speed;
}

float Entity::getSpeed()
{
	return this->speed;
}


// Collision
void Entity::setColliderRadius(float colRad)
{
	this->colRad = colRad;
}

float Entity::getColliderRadius()
{
	return this->colRad;
}
