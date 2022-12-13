#pragma once
#include "entity.h"
#include "../Lighting/point.h"

class Crystal : public Entity
{
public:
	Crystal(GameObject* model);
	~Crystal();
	
	Light::Point* light;
};