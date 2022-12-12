#pragma once
#include "dataOBJ.h"

std::vector<DataOBJ> readObj(const std::string& objPathName, glm::vec3 color = glm::vec3(1.0, 0.0, 0.0)) {

	std::vector<unsigned int> vertexIndices;
	std::vector<unsigned int> uvIndices;
	std::vector<unsigned int> normalIndices;

	std::vector<glm::vec3> tempVertices;
	std::vector<glm::vec2> tempUvs;
	std::vector<glm::vec3> tempNormals;

	std::ifstream objFile(objPathName);
	std::string singleline = "";

	if (!objFile.is_open())
	{
		std::cout << "Error while reading obj data file" << std::endl;
		exit(EXIT_FAILURE);
	}

	while (!objFile.eof())
	{
		std::stringstream ss;
		std::getline(objFile, singleline);

		std::string dataType;
		ss.clear();
		ss.str(singleline);
		ss >> dataType;

		if (dataType == "v") {
			glm::vec3 vertices{};
			ss >> vertices.x >> vertices.y >> vertices.z;
			tempVertices.push_back(vertices);
		}
		else if (dataType == "vt") {
			glm::vec2 textCoords{};
			ss >> textCoords.x >> textCoords.y;
			tempUvs.push_back(textCoords);
		}
		else if (dataType == "vn") {
			glm::vec3 normals{};
			ss >> normals.x >> normals.y >> normals.z;
			tempNormals.push_back(normals);
		}
		else if (dataType == "f") {
			int i = 0;
			int index = 0;
			while (ss >> index) {
				switch (i) {
				case 0:
					vertexIndices.push_back(index);
					break;
				case 1:
					uvIndices.push_back(index);
					break;
				case 2:
					normalIndices.push_back(index);
					break;
				}

				if (ss.peek() == '/') {
					ss.ignore(1, '/');
					i++;
				}
				else if (ss.peek() == ' ') {
					ss.ignore(1, ' ');
					i++;
				}

				if (i > 2) {
					i = 0;
				}
			}
		}
	}

	objFile.close();

	std::vector<DataOBJ> objData;

	for (unsigned int i = 0; i < vertexIndices.size(); i++) {

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		glm::vec3 vertex = tempVertices[vertexIndex - 1];
		glm::vec2 uv = tempUvs[uvIndex - 1];
		glm::vec3 normal = tempNormals[normalIndex - 1];

		// Put the attributes in buffers

		DataOBJ data{};
		data.vertex = vertex;
		data.uv = uv;
		data.normal = normal;
		data.color = color;

		objData.push_back(data);
	}

	return objData;
}