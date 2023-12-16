#pragma once
#include "pch.h"
#include "entity.h"
#include <string>

/* --->>> Constructors / Destructor <<<--- */
Entity::Entity(GameObject* gameObj, std::string name)
{
	_gameObj = gameObj;
	setName(name);
}

Entity::~Entity()
{
	Debug::Log("Destroyed entity " + _name);
	delete _gameObj;
}


/* --->>> Update <<<--- */
void Entity::update(float deltaTime)
{
}


/* --->>> Drawing <<<--- */
void Entity::draw(ShaderProgram* shaderProgram)
{
	_gameObj->draw(shaderProgram);
}


/* --->>> Destroying <<<--- */
void Entity::destroy()
{
	delete this;
}


/* --->>> Naming <<<--- */
void Entity::setName(std::string name)
{
	_name = name;
}

std::string Entity::getName()
{
	return _name;
}


/* --->>> Position <<<--- */
void Entity::setPosition(const glm::vec3 position)
{
	_gameObj->setPosition(position);
}

glm::vec3 Entity::getPosition()
{
	return _gameObj->getPosition();
}

void Entity::setOrigin(const glm::vec3 origin)
{
	_gameObj->setOrigin(origin);
}


/* --->>> Rotation <<<--- */
void Entity::setRotation(const glm::vec3 rotation)
{
	_gameObj->setRotation(rotation);
}

glm::vec3 Entity::getRotation()
{
	return _gameObj->getRotation();
}


/* --->>> Scale <<<--- */
void Entity::setScale(const glm::vec3 scale)
{
	_gameObj->setScale(scale);
}


/* --->>> Direction <<<---*/
void Entity::setDirection(glm::vec3 direction)
{
	_direction = direction;
}

glm::vec3 Entity::getDirection()
{
	return _direction;
}

void Entity::moveWithDirection(float deltaTime)
{
	glm::vec3 newPosition =  getPosition() + (deltaTime * _speed * _direction);
	setPosition(newPosition);
}


/* --->>> Speed <<<--- */
void Entity::setSpeed(float speed)
{
	_speed = speed;
}

float Entity::getSpeed()
{
	return _speed;
}


/* --->>> Collision <<<--- */
void Entity::setColliderRadius(float colRad)
{
	_colRad = colRad;
}

float Entity::getColliderRadius()
{
	return _colRad;
}
