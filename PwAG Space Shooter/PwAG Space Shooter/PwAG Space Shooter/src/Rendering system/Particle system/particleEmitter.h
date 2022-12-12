#pragma once
#include "particle.h"
#include "../Texture/texture.h"

class ParticleEmitter
{
public:
	ParticleEmitter(const glm::vec3& position, const glm::vec3& startVelocity, const glm::vec3& startAcceleration, const glm::vec3& range, const Texture& texture, const glm::vec2& scale = { 1.0f, 1.0f });
	ParticleEmitter(const ParticleEmitter&) = delete;
	ParticleEmitter(ParticleEmitter&&) noexcept;

	ParticleEmitter& operator=(const ParticleEmitter&) = delete;
	ParticleEmitter& operator=(ParticleEmitter&&) noexcept;

	void update(float deltaTime);

	void render(const ShaderProgram& shader, const glm::vec3& cameraPosition);

#pragma region Inline functions
	bool isActive() const
	{
		return active;
	}
	const glm::vec3& getPosition() const
	{
		return position;
	}

	void setActive(bool isActive)
	{
		this->active = isActive;
	}
	void setAccelerationUpdateFunction(std::function<void(float deltaTime)> function)
	{
		accelerationUpdateFunction = std::move(function);
	}
#pragma endregion
private:
	bool active = true;

	glm::vec3 position;
	glm::vec3 particleStartVelocity;
	glm::vec3 particleStartAcceleration;

	std::function<void(float deltaTime)> accelerationUpdateFunction =
		[&](float) mutable -> void
	{};

	glm::vec3 range;

	glm::vec2 scale;
	const Texture* texture;

	static uint32_t maxParticles;
	std::vector<Particle> particles;

	const float timeToCreateAnotherParticle = 0.4f;
	float timePassed = 0.0f;
};

