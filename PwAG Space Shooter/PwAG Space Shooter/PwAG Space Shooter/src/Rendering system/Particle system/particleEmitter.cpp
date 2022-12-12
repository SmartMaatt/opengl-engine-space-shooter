#include "pch.h"
#include "particleEmitter.h"

uint32_t ParticleEmitter::maxParticles = 100;

ParticleEmitter::ParticleEmitter(const glm::vec3& position, const glm::vec3& startVelocity, const glm::vec3& startAcceleration, const glm::vec3& range, const Texture& texture, const glm::vec2& scale)
	: position(position), particleStartVelocity(startVelocity), particleStartAcceleration(startAcceleration), range(range), scale(scale), texture(&texture)
{
}

ParticleEmitter::ParticleEmitter(ParticleEmitter&& other) noexcept
	: position(other.position), particleStartVelocity(other.particleStartVelocity), particleStartAcceleration(other.particleStartAcceleration), accelerationUpdateFunction(std::move(other.accelerationUpdateFunction)),
	range(other.range), scale(other.scale), particles(std::move(other.particles)), timePassed(other.timePassed), texture(other.texture)
{
}

ParticleEmitter& ParticleEmitter::operator=(ParticleEmitter&& other) noexcept
{
	if(this != &other)
	{
		position = other.position;
		particleStartVelocity = other.particleStartVelocity;
		particleStartAcceleration = other.particleStartAcceleration;
		accelerationUpdateFunction = std::move(other.accelerationUpdateFunction);

		range = other.range;
		scale = other.scale;
		particles = std::move(other.particles);
		timePassed = other.timePassed;
		texture = other.texture;
	}

	return *this;
}

void ParticleEmitter::update(float deltaTime)
{
	if(!particles.empty())
	{
		particles.erase(std::remove_if(
			particles.begin(),
			particles.end(),
			[](const Particle& particle) -> bool
			{
				return particle.getLifetime().passed >= particle.getLifetime().max;
			}),
			particles.end()
		);

		for(auto iter = particles.begin(); iter != particles.end(); iter++)
		{
			iter->update(deltaTime);
		}
	}
	timePassed += deltaTime;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distr(-1.0, 1.0);

	while(timePassed >= timeToCreateAnotherParticle)
	{
		timePassed -= timeToCreateAnotherParticle;

		if(particles.size() < maxParticles)
		{
			glm::vec3 posDiff =
			{
				distr(gen) * range.x,
				distr(gen) * range.y,
				distr(gen) * range.z,
			};
			particles.emplace_back(this->position + posDiff, particleStartVelocity, particleStartAcceleration);
			particles.back().setAccelerationUpdateFunction(accelerationUpdateFunction);
		}
	}
}

void ParticleEmitter::render(const ShaderProgram& shader, const glm::vec3& cameraPosition)
{
	texture->bindTexture(0);
	shader.setVec2f("scale", scale);
/*
	std::sort(particles.begin(), particles.end(), 
			  [&cameraPosition](const Particle& left, const Particle& right) -> bool
			  {
				  return glm::distance2(cameraPosition, left.getPosition()) > glm::distance2(cameraPosition, right.getPosition());
			  });
*/
	for(auto& particle : particles)
	{
		particle.render(shader);
	}

	texture->unbindTexture();
}
