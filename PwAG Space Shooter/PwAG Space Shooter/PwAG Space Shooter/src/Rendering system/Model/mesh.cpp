#include "pch.h"
#include "mesh.h"

Mesh::Mesh() {

}

Mesh::Mesh(DataOBJ* vertices, int verticesSize, GLuint* indices, int indicesSize) {
	
	this->verticesSize = verticesSize;
	this->indicesSize = indicesSize;

	this->vertices = new DataOBJ[this -> verticesSize];
	for (int i = 0; i < this->verticesSize; i++) {
		this->vertices[i] = vertices[i];
	}

	this->indices = new GLuint[this->indicesSize];
	for (int i = 0; i < this->indicesSize; i++) {
		this->indices[i] = indices[i];
	}
}

void Mesh::setMeshUniform(ShaderProgram* shaderProgram) {
	shaderProgram->setMat4("ModelMatrix", matrixModel);
}

void Mesh::setMatrixModel(glm::vec3 position, glm::vec3 origin, glm::vec3 rotation, glm::vec3 scale)
{
	this->matrixModel = glm::mat4(1.f);
	this->matrixModel = glm::translate(this->matrixModel, origin);
	this->matrixModel = glm::rotate(this->matrixModel, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
	this->matrixModel = glm::rotate(this->matrixModel, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
	this->matrixModel = glm::rotate(this->matrixModel, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
	this->matrixModel = glm::translate(this->matrixModel, position - origin);
	this->matrixModel = glm::scale(this->matrixModel, scale);
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	if (this->indicesSize > 0)
	{
		glDeleteBuffers(1, &EBO);
	}

	delete[] this->vertices;
	delete[] this->indices;
}