#pragma once
#include "pch.h"
#include "entity.h"
#include "bullet.h"
#include <string>

Bullet::Bullet(GameObject* model, float dieAge) : Entity(model) 
{
	this->dieAge = dieAge;
}

Bullet::~Bullet()
{
}

void Bullet::calcAge(float deltaTime)
{
	age += deltaTime;
	dead = age > dieAge;
}

bool Bullet::isDead()
{
	return this->dead;
}