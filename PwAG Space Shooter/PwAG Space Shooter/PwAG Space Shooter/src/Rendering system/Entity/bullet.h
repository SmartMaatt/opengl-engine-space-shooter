#pragma once
#include "livingEntity.h"
#include "../Lighting/point.h"

class Bullet : public LivingEntity
{
public:
	// Constructors / Destructor
	Bullet(GameObject* gameObj, std::string name, float lifeSpan, Player* player);
	~Bullet();

	// Update
	void update(float deltaTime);

	// Drawing
	void draw(ShaderProgram* shaderProgram);

	// Destroying
	void destroy();

	// Getters
	Light::Point* getLight();

private:
	Light::Point* _light;
};