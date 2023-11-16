#pragma once
#include "dataOBJ.h"
#include "indexedDataOBJ.h"

class Mesh
{
public:
	Mesh();
	Mesh(DataOBJ objData, glm::vec3 offset);
	Mesh(Mesh& src);

	void drawMesh();

	// Uniforms
	void setMeshUniform(ShaderProgram* shaderProgram);
	void setMatrixModel(glm::vec3 meshPosition, glm::vec3 meshOrigin, glm::vec3 meshRotation, glm::vec3 meshScale);

	// Getters
	glm::vec3 getOffset();
	DataOBJ getMeshData();
	IndexedDataOBJ getIndexedMeshData();

	virtual ~Mesh();

private:
	void initBuffers();

	DataOBJ meshData;
	IndexedDataOBJ indexedData;

	glm::vec3 offset;
	std::vector<glm::vec3> offsets;

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

