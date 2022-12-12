#include "pch.h"
#include "particle.h"

#pragma region Lifetime
float Particle::Lifetime::max = 3.0f;

Particle::Lifetime::Lifetime(float passed)
	: passed(passed)
{
}

Particle::Lifetime::Lifetime(const Lifetime& other)
	: passed(other.passed)
{
}

Particle::Lifetime::Lifetime(Lifetime&& other) noexcept
	: passed(other.passed)
{
}

Particle::Lifetime& Particle::Lifetime::operator=(const Lifetime& other)
{
	if(this != &other)
	{
		passed = other.passed;
	}

	return *this;
}

Particle::Lifetime& Particle::Lifetime::operator=(Lifetime&& other) noexcept
{
	if(this != &other)
	{
		passed = other.passed;
	}

	return *this;
}
#pragma endregion

Particle::Particle(const glm::vec3& startPosition, const glm::vec3& startVelocity, const glm::vec3& startAcceleration)
	: position(startPosition), velocity(startVelocity), acceleration(startAcceleration)
{
	float vertices[] = { 0.0f, 0.0f, 0.0f };

	vao.bind();
	vbo.bind();

	vbo.bufferData(vertices, sizeof(vertices));
	vbo.setAttributesPointers(0, 3, GL_FLOAT, 3 * sizeof(float), nullptr);

	lifetime.passed = 0.0f;
}

Particle::Particle(Particle&& other) noexcept
	: position(other.position), velocity(other.velocity), acceleration(other.acceleration), accelerationUpdateFunction(std::move(other.accelerationUpdateFunction)),
	lifetime(std::move(other.lifetime)), vao(std::move(other.vao)), vbo(std::move(other.vbo))
{
}

Particle& Particle::operator=(Particle&& other) noexcept
{
	if(this != &other)
	{
		position = other.position;
		velocity = other.velocity;
		acceleration = other.acceleration;
		accelerationUpdateFunction = std::move(other.accelerationUpdateFunction);

		lifetime = other.lifetime;
		vao = std::move(other.vao);
		vbo = std::move(other.vbo);
	}

	return *this;
}

void Particle::update(float deltaTime)
{

	lifetime.passed += deltaTime;

	accelerationUpdateFunction(deltaTime);
	velocity += acceleration * deltaTime;
	position += velocity * deltaTime;
}

void Particle::render(const ShaderProgram& shader)
{

	auto model = glm::mat4(1.0f);
	model = glm::translate(model, this->position);
	shader.setMat4("ModelMatrix", model);

	vao.bind();
	glDrawArrays(GL_POINTS, 0, 1);
}
