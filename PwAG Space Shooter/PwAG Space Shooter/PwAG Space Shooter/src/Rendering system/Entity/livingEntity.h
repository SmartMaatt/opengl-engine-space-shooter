#pragma once
#include "entity.h"
#include "../Rendering system/Model/gameObject.h"

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
	float getAge();

protected:
	// Age parameters
	float _lifeSpan = 0;
	float _age = 0.0f;
	bool _dead = false;

private:
	void _calcAge(float deltaTime);
};