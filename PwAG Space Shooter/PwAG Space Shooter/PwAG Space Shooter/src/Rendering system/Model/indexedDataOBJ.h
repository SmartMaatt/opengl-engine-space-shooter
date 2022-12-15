#pragma once
#include <vector>
#include <GLM/include/glm.hpp>

struct IndexedDataOBJ
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> colors;
	std::vector<glm::vec3> normals;

	std::vector <glm::vec3> tangents;
	std::vector <glm::vec3> bittangents;
	std::vector <glm::vec2> uvs;

	std::vector<unsigned short> indices;
};