#pragma once
#include "pch.h"
#include "entity.h"

Entity::Entity(GameObject* model)
{
	this->model = model;
}

Entity::~Entity()
{
	delete this->model;
}

void Entity::drawEntity(ShaderProgram* shaderProgram)
{
	this->model->draw(shaderProgram);
}

// Position
void Entity::setPosition(const glm::vec3 position)
{
	this->model->setPosition(position);
}

glm::vec3 Entity::getPosition()
{
	return this->model->getPosition();
}

void Entity::setOrigin(const glm::vec3 origin)
{
	this->model->setOrigin(origin);
}

// Rotation
void Entity::setRotation(const glm::vec3 rotation)
{
	this->model->setRotation(rotation);
}

glm::vec3 Entity::getRotation()
{
	return this->model->getRotation();
}

// Scale
void Entity::setScale(const glm::vec3 scale)
{
	this->model->setScale(scale);
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