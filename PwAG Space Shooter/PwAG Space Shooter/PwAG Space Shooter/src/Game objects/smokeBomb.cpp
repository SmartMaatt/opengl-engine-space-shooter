#include "pch.h"
#include "smokeBomb.h"

float SmokeBomb::maxDurationTime = 10.0f;

SmokeBomb::SmokeBomb(const glm::vec3& position)
	: position(position), emitter(position, { 0.0f, 0.1f, 0.0f }, { 0.0f, 0.0f ,0.0f }, { 2.0f, 0.3f, 2.0f }, ResourceManager::getInstance().getTexture("smoke"), glm::vec2(4.0f, 4.0f))
{
}

void SmokeBomb::update(float deltaTime)
{
	durationTime += deltaTime;
	emitter.update(deltaTime);
}

void SmokeBomb::render(float deltaTime, const ShaderProgram& particleShader, const glm::vec3& cameraPosition)
{
	emitter.render(particleShader, cameraPosition);
}