#include "pch.h"
#include "attenuation.h"

/* --->>> Constructors / Destructor <<<--- */
Light::Attenuation::Attenuation(float constant, float linear, float quadratic) :
	_constant(constant), _linear(linear), _quadratic(quadratic)
{
}

/* --->>> Getters / Setters <<<--- */
void Light::Attenuation::setAttenuationByRange(float _range)
{
	_linear = 4.5452f * powf(_range, -1.004f);
	_quadratic = 82.445f * powf(_range, -2.019f);
}
