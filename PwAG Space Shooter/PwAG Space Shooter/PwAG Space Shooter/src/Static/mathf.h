#pragma once
#include <random>
#include "GLM/include/glm.hpp"

class Mathf
{
public:
	// Constructors / Destructor
	Mathf() = delete;

	// Randomization
	static float randVal(float min, float max);
	static glm::vec3 randCoordsInSphere(float radius);

	// Collisions
	static bool areSpheresCollided(glm::vec3 center1, float rad1, glm::vec3 center2, float rad2);

	// Matrices
	static glm::mat4 calculateRotationMatrix(glm::vec3 rotation);

	// Vectors
	static glm::vec3 zeroVec();
	static glm::vec3 oneVec();
};