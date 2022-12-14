#pragma once
#include "entity.h"
#include "../Lighting/point.h"

class Bullet : public Entity
{
public:
	Bullet(GameObject* model, float dieAge);
	~Bullet();
	
	void calcAge(float deltaTime);
	bool isDead();

	Light::Point* light;

private:
	float age = 0.0f;
	float dieAge = 7.0f;
	bool dead = false;
};