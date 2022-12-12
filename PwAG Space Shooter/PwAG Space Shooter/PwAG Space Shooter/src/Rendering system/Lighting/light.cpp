#include "pch.h"
#include "light.h"

Light::Light::Light(const glm::vec3& color)
	: color(color)
{
	this->ambient = color * 0.05f;
	this->specular = color * 1.0f;
	this->diffuse = color * 0.8f;
}
