#pragma once
#include "livingEntity.h"
#include "../Lighting/point.h"

class Bullet : public LivingEntity
{
public:
	// Constructors / Destructor
	Bullet(GameObject* gameObj, std::string name, float lifeSpan, glm::vec3 position, glm::vec3 direction, glm::vec3 lightColor);
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