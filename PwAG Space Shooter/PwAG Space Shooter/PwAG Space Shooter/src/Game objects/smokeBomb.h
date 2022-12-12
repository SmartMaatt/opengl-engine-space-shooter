#pragma once
#include "../Rendering system/Particle system/particleEmitter.h"

class SmokeBomb
{
public:
	SmokeBomb(const glm::vec3& position);

	void update(float deltaTime);
	void render(float deltaTime, const ShaderProgram& particleShader, const glm::vec3& cameraPosition);

#pragma region Inline functions
	float getMaxDurationTime() const
	{
		return maxDurationTime;
	}
	float getDurationTime() const
	{
		return durationTime;
	}
	const glm::vec3& getPosition() const
	{
		return position;
	}
#pragma endregion
private:
	glm::vec3 position;
	ParticleEmitter emitter;
	static float maxDurationTime; //in sec
	float durationTime = 0.0f;
};

