#pragma once
#include "entity.h"
#include "../Lighting/point.h"

class Medkit : public Entity
{
public:
	// Constructors / Destructor
	Medkit(GameObject* gameObj, std::string name, float worldRadius);
	~Medkit();
	
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