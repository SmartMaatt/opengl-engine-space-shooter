#include "pch.h"
#include "mesh.h"
#include "vboIndexer.h"

Mesh::Mesh() 
{
}

Mesh::Mesh(IndexedDataOBJ objData, glm::vec3 offset, int instances)
{
	this->indexedData = objData;
	this->offset = offset;
	this->instances = instances;

	for (unsigned int i = 0; i < indexedData.vertices.size(); i++)
	{
		offsets.push_back(offset);
	}
	initBuffers();
}

void Mesh::initBuffers()
{
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	glGenBuffers(1, &verticesBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
	glBufferData(GL_ARRAY_BUFFER, indexedData.vertices.size() * sizeof(glm::vec3), &(indexedData.vertices[0]), GL_STATIC_DRAW);

	glGenBuffers(1, &colorsBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorsBuffer);
	glBufferData(GL_ARRAY_BUFFER, indexedData.colors.size() * sizeof(glm::vec3), &(indexedData.colors[0]), GL_STATIC_DRAW);

	glGenBuffers(1, &normalsBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
	glBufferData(GL_ARRAY_BUFFER, indexedData.normals.size() * sizeof(glm::vec3), &(indexedData.normals[0]), GL_STATIC_DRAW);

	glGenBuffers(1, &tangentBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, tangentBuffer);
	glBufferData(GL_ARRAY_BUFFER, indexedData.tangents.size() * sizeof(glm::vec3), &(indexedData.tangents[0]), GL_STATIC_DRAW);

	glGenBuffers(1, &bitangentBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, bitangentBuffer);
	glBufferData(GL_ARRAY_BUFFER, indexedData.bittangents.size() * sizeof(glm::vec3), &(indexedData.bittangents[0]), GL_STATIC_DRAW);

	glGenBuffers(1, &uvsBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvsBuffer);
	glBufferData(GL_ARRAY_BUFFER, indexedData.uvs.size() * sizeof(glm::vec2), &(indexedData.uvs[0]), GL_STATIC_DRAW);

	glGenBuffers(1, &offsetBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, offsetBuffer);
	glBufferData(GL_ARRAY_BUFFER, offsets.size() * sizeof(glm::vec3), &offsets[0], GL_STATIC_DRAW);

	glGenBuffers(1, &elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexedData.indices.size() * sizeof(unsigned short), &indexedData.indices[0], GL_STATIC_DRAW);
}

void Mesh::drawMesh()
{
	glBindVertexArray(vertexArrayID);

	// Vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Colors
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorsBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Tangents
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, tangentBuffer);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Bitangents
	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, bitangentBuffer);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Uvs
	glEnableVertexAttribArray(5);
	glBindBuffer(GL_ARRAY_BUFFER, uvsBuffer);
	glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Offset
	glEnableVertexAttribArray(6);
	glBindBuffer(GL_ARRAY_BUFFER, offsetBuffer);
	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glDrawElements(GL_TRIANGLES, indexedData.indices.size(), GL_UNSIGNED_SHORT, (void*)0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);
	glDisableVertexAttribArray(6);
}

void Mesh::setMeshUniform(ShaderProgram* shaderProgram) 
{
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

Mesh::~Mesh() 
{
	glDeleteBuffers(1, &verticesBuffer);
	glDeleteBuffers(1, &colorsBuffer);
	glDeleteBuffers(1, &normalsBuffer);
	glDeleteBuffers(1, &tangentBuffer);
	glDeleteBuffers(1, &bitangentBuffer);
	glDeleteBuffers(1, &uvsBuffer);
	glDeleteBuffers(1, &offsetBuffer);

	glDeleteBuffers(1, &elementBuffer);
	glDeleteVertexArrays(1, &vertexArrayID);
}