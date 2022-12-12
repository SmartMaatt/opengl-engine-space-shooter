#pragma once

class Particle
{
public:
	struct Lifetime
	{
		explicit Lifetime(float passed = 0);
		Lifetime(const Lifetime&);
		Lifetime(Lifetime&&) noexcept;

		Lifetime& operator=(const Lifetime&);
		Lifetime& operator=(Lifetime&&) noexcept;

		static float max; //in sec
		float passed;
	};

	Particle(const glm::vec3& startPosition, const glm::vec3& startVelocity, const glm::vec3& startAcceleration);
	Particle(const Particle&) = delete;
	Particle(Particle&&) noexcept;
	Particle& operator=(const Particle&) = delete;
	Particle& operator=(Particle&&) noexcept;

#pragma region Inline functions
	const glm::vec3& getPosition() const
	{
		return position;
	}
	const Particle::Lifetime& getLifetime() const
	{
		return lifetime;
	}

	void setAccelerationUpdateFunction(std::function<void(float deltaTime)> function)
	{
		accelerationUpdateFunction = std::move(function);
	}
#pragma endregion

	void update(float deltaTime);
	void render(const ShaderProgram& shader);
private:
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;

	std::function<void(float deltaTime)> accelerationUpdateFunction = 
		[&](float) mutable -> void
	{};

	Lifetime lifetime;

	VAO vao;
	VBO vbo;
};

