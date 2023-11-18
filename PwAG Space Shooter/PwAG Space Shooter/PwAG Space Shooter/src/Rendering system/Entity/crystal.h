#pragma once
#include "entity.h"
#include "../Lighting/point.h"

class Crystal : public Entity
{
public:
	// Constructors / Destructor
	Crystal(GameObject* gameObj, std::string name, float worldRadius);
	~Crystal();
	
	// Update
	void update(float deltaTime);

	// Drawing
	void draw(ShaderProgram* shaderProgram);

	// Destroying
	void destroy();

	Light::Point* light;
};