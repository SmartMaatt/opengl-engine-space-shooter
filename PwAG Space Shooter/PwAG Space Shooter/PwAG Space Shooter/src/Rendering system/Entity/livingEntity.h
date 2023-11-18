#pragma once
#include "entity.h"
#include "../../Game objects/gameObject.h"

class LivingEntity : public Entity
{
public:
	// Constructors / Destructor
	LivingEntity(GameObject* gameObj, std::string name, float lifeSpan);
	~LivingEntity();

	// Update
	void update(float deltaTime);

	// Drawing
	void draw(ShaderProgram* shaderProgram);

	// Destroying
	void destroy();

	// Life span
	bool isDead();

protected:
	float lifeSpan = 0;
	float age = 0.0f;

	bool dead = false;

private:
	void calcAge(float deltaTime);
};