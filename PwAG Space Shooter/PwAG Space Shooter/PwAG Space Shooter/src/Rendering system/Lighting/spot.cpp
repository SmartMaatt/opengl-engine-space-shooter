#include "pch.h"
#include "spot.h"

Light::Spot::Spot(const glm::vec3& position, const glm::vec3& color, float cutoff)
	: Light(color), position(position), innerCutoff(cutoff * 0.98f), outerCutoff(cutoff * 1.02f)
{
}

Light::Spot::Spot(const glm::vec3& position, const glm::vec3& color, float innerCutoff, float outerCutoff)
	: Light(color), position(position), innerCutoff(innerCutoff), outerCutoff(outerCutoff)
{
}
