#include "pch.h"
#include "mathf.h"

/* --->>> Randomization <<<--- */
float Mathf::randVal(float min, float max)
{
	static std::mt19937 generator(std::random_device{}());
	std::uniform_real_distribution<float> distribution(min, max);
	return distribution(generator);
}

glm::vec3 Mathf::randCoordsInSphere(float radius)
{
	float x = randVal(-1, 1);
	float y = randVal(-1, 1);
	float z = randVal(-1, 1);

	float mag = glm::sqrt((x * x) + (y * y) + (z * z));
	float d = randVal(0, radius) / mag;

	x *= d;
	y *= d;
	z *= d;
	return glm::vec3(x, y, z);
}


/* --->>> Collisions <<<---*/
bool Mathf::areSpheresCollided(glm::vec3 center1, float rad1, glm::vec3 center2, float rad2)
{
	float radSum = rad1 + rad2;
	float distance = glm::distance(center1, center2);

	return (radSum > distance);
}


/* --->>> Matrices <<<--- */
glm::mat4 Mathf::calculateRotationMatrix(glm::vec3 rotation)
{
	glm::mat4 rotationMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	return rotationMatrix;
}


/* --->>> Vectors <<<---*/
glm::vec3 Mathf::zeroVec()
{
	return glm::vec3(0);
}

glm::vec3 Mathf::oneVec()
{
	return glm::vec3(1);
}
