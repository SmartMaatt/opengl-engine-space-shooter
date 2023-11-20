#include "pch.h"
#include "ShaderLightProgram.h"

/* --->>> Setters <<<--- */
void ShaderLightProgram::setNumberOfLights(int numberOfLights)
{
	setInt("pointLightsCount", static_cast<int>(numberOfLights));
}

void ShaderLightProgram::setLightUniforms(Light::Point light, std::string& index)
{
	setVec3f(index + "position",	light.getPosition());
	setVec3f(index + "diffuse",		light.getDiffuse());
	setVec3f(index + "specular",	light.getSpecular());
										 
	setFloat(index + "constant",	light.getAttenuation().getConstant());
	setFloat(index + "linear",		light.getAttenuation().getLinear());
	setFloat(index + "quadratic",	light.getAttenuation().getQuadratic());
}
