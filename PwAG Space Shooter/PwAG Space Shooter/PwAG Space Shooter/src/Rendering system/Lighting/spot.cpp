#include "pch.h"
#include "spot.h"

/* --->>> Constructors / Destructor <<<--- */
Light::Spot::Spot(const glm::vec3& _position, const glm::vec3& color, float cutoff) :
	Light(color), _position(_position), _innerCutoff(cutoff * 0.98f), _outerCutoff(cutoff * 1.02f)
{
}

Light::Spot::Spot(const glm::vec3& _position, const glm::vec3& color, float _innerCutoff, float _outerCutoff) :
	Light(color), _position(_position), _innerCutoff(_innerCutoff), _outerCutoff(_outerCutoff)
{
}
