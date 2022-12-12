#pragma once

struct DataOBJ
{
	glm::vec3 vertex;
	glm::vec3 color = glm::vec3(1.0, 0.0, 0.0);
	glm::vec3 normal;

	glm::vec3 tangent;
	glm::vec3 bittangent;

	glm::vec2 uv;
};

