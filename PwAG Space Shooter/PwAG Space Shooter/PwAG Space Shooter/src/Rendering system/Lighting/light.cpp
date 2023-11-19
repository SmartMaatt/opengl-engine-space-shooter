#include "pch.h"
#include "light.h"

/* --->>> Constructors / Destructor <<<--- */
Light::Light::Light(const glm::vec3& color) : _color(color)
{
	_ambient =	color * 0.05f;
	_specular = color * 1.0f;
	_diffuse =	color * 0.8f;
}
