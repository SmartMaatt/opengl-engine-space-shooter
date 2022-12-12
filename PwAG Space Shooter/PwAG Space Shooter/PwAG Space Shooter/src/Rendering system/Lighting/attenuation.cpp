#include "pch.h"
#include "attenuation.h"

Light::Attenuation::Attenuation(float constant, float linear, float quadratic)
	: constant(constant), linear(linear), quadratic(quadratic)
{
}

void Light::Attenuation::setAttenuationByRange(float range)
{
	linear = 4.5452f * powf(range, -1.004f);
	quadratic = 82.445f * powf(range, -2.019f);
}
