#pragma once
#include "dataOBJ.h"
#include "indexedDataOBJ.h"

class Mesh
{
public:
	Mesh();
	Mesh(IndexedDataOBJ objData, glm::vec3 offset, int instances);

	void drawMesh();

	void setMeshUniform(ShaderProgram* shaderProgram);
	void setMatrixModel(glm::vec3 meshPosition, glm::vec3 meshOrigin, glm::vec3 meshRotation, glm::vec3 meshScale);

	virtual ~Mesh();

private:
	void initBuffers();

	IndexedDataOBJ indexedData;

	glm::vec3 offset;
	std::vector<glm::vec3> offsets;
	int instances = 0;

	glm::mat4 matrixModel;

	GLuint vertexArrayID;
	GLuint elementBuffer;

	GLuint verticesBuffer;
	GLuint colorsBuffer;
	GLuint normalsBuffer;
	GLuint tangentBuffer;
	GLuint bitangentBuffer;
	GLuint uvsBuffer;
	GLuint offsetBuffer;
};

