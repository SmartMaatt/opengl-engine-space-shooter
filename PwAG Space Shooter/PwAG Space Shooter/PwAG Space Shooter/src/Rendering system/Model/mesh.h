#pragma once
#include "dataOBJ.h"

// data set for vertices, indices, textures
class Mesh
{
public:
	Mesh();
	Mesh(DataOBJ* vertices, int verticesSize, GLuint* indices, int indicesSize);

	void setMeshUniform(ShaderProgram* shaderProgram);
	void setMatrixModel(glm::vec3 meshPosition, glm::vec3 meshOrigin, glm::vec3 meshRotation, glm::vec3 meshScale);

	virtual ~Mesh();
private:
	DataOBJ* vertices;
	GLuint* indices;

	int verticesSize;
	int indicesSize;

	glm::mat4 matrixModel;

	GLuint VAO, VBO, EBO;

	friend class GameObject;
};

