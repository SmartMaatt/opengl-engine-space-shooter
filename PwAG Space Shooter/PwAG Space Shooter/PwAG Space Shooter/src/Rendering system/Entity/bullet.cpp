#pragma once
#include "pch.h"
#include "livingEntity.h"
#include "bullet.h"
#include <string>

/* --->>> Constructors / Destructor <<<--- */
Bullet::Bullet(GameObject* gameObj, std::string name, float lifeSpan, Player* player) : LivingEntity(gameObj, name, lifeSpan)
{
	// Position
	setPosition(player->getCameraPosition() + player->getDirection() * 0.3f);
	setOrigin(player->getCameraPosition());

	// Scale
	setScale(Mathf::oneVec() * 0.05f);
	setColliderRadius(0.5f);

	// Movement
	setDirection(player->getDirection());
	setSpeed(5);

	// Light
	_light = new Light::Point(getPosition(), { 0,0,1 });
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
