#pragma once
#include "ShaderProgram.h"
#include "../Rendering system/Lighting/point.h"

class ShaderLightProgram : public ShaderProgram
{
public:
	// Constructors / Destructor
	ShaderLightProgram() = default;
	ShaderLightProgram(const ShaderLightProgram&) = delete;
	ShaderLightProgram(ShaderLightProgram&&) noexcept = default;
	~ShaderLightProgram() = default;

	// Operators
	ShaderLightProgram& operator=(const ShaderLightProgram&) = delete;
	ShaderLightProgram& operator=(ShaderLightProgram&&) noexcept = default;

	// Setters
	void setNumberOfLights(int numberOfLights);
	void setLightUniforms(Light::Point light, std::string& index);
};
