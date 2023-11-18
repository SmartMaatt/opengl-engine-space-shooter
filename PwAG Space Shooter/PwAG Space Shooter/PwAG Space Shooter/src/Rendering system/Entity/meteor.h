#pragma once
#include "entity.h"
#include "../Lighting/point.h"

class Meteor : public Entity
{
public:
	// Constructors / Destructor
	Meteor(GameObject* gameObj, std::string name, float worldRadius);
	~Meteor();

	// Update
	void update(float deltaTime);

	// Drawing
	void draw(ShaderProgram* shaderProgram);

	// Destroying
	void destroy();

	// Collision
	void changeDirectionOnCollision();
};