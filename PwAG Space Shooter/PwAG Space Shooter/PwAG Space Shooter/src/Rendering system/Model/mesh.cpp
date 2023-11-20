#include "pch.h"
#include "mesh.h"
#include "vboIndexer.h"

/* --->>> Constructors / Destructor <<<--- */
Mesh::Mesh()
{
}

Mesh::Mesh(DataOBJ meshData, glm::vec3 offset)
{
	_meshData = meshData;
	_indexedData = ObjectDataIndexer::indexVBO_TBN(meshData);
	_offset = offset;

	for (unsigned int i = 0; i < _indexedData.vertices.size(); i++)
	{
		_offsets.push_back(_offset);
	}
	_initBuffers();
}

Mesh::Mesh(Mesh& src)
{
	_meshData = src.getMeshData();
	_indexedData = src.getIndexedMeshData();
	_offset = src.getOffset();

	for (unsigned int i = 0; i < _indexedData.vertices.size(); i++)
	{
		_offsets.push_back(_offset);
	}
	_initBuffers();
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &_verticesBuffer);
	glDeleteBuffers(1, &_colorsBuffer);
	glDeleteBuffers(1, &_normalsBuffer);
	glDeleteBuffers(1, &_tangentBuffer);
	glDeleteBuffers(1, &_bitangentBuffer);
	glDeleteBuffers(1, &_uvsBuffer);
	glDeleteBuffers(1, &_offsetBuffer);

	glDeleteBuffers(1, &_elementBuffer);
	glDeleteVertexArrays(1, &_vertexArrayID);
}


/* --->>> Initialization <<<--- */
void Mesh::_initBuffers()
{
	glGenVertexArrays(1, &_vertexArrayID);
	glBindVertexArray(_vertexArrayID);

	glGenBuffers(1, &_verticesBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _verticesBuffer);
	glBufferData(GL_ARRAY_BUFFER, _indexedData.vertices.size() * sizeof(glm::vec3), &(_indexedData.vertices[0]), GL_STATIC_DRAW);

	glGenBuffers(1, &_colorsBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _colorsBuffer);
	glBufferData(GL_ARRAY_BUFFER, _indexedData.colors.size() * sizeof(glm::vec3), &(_indexedData.colors[0]), GL_STATIC_DRAW);

	glGenBuffers(1, &_normalsBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _normalsBuffer);
	glBufferData(GL_ARRAY_BUFFER, _indexedData.normals.size() * sizeof(glm::vec3), &(_indexedData.normals[0]), GL_STATIC_DRAW);

	glGenBuffers(1, &_tangentBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _tangentBuffer);
	glBufferData(GL_ARRAY_BUFFER, _indexedData.tangents.size() * sizeof(glm::vec3), &(_indexedData.tangents[0]), GL_STATIC_DRAW);

	glGenBuffers(1, &_bitangentBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _bitangentBuffer);
	glBufferData(GL_ARRAY_BUFFER, _indexedData.bittangents.size() * sizeof(glm::vec3), &(_indexedData.bittangents[0]), GL_STATIC_DRAW);

	glGenBuffers(1, &_uvsBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uvsBuffer);
	glBufferData(GL_ARRAY_BUFFER, _indexedData.uvs.size() * sizeof(glm::vec2), &(_indexedData.uvs[0]), GL_STATIC_DRAW);

	glGenBuffers(1, &_offsetBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _offsetBuffer);
	glBufferData(GL_ARRAY_BUFFER, _offsets.size() * sizeof(glm::vec3), &_offsets[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexedData.indices.size() * sizeof(unsigned short), &_indexedData.indices[0], GL_STATIC_DRAW);
}


/* --->>> Drawing <<<--- */
void Mesh::drawMesh()
{
	glBindVertexArray(_vertexArrayID);

	// Vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _verticesBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Colors
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, _colorsBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, _normalsBuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Tangents
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, _tangentBuffer);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Bitangents
	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, _bitangentBuffer);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Uvs
	glEnableVertexAttribArray(5);
	glBindBuffer(GL_ARRAY_BUFFER, _uvsBuffer);
	glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Offset
	glEnableVertexAttribArray(6);
	glBindBuffer(GL_ARRAY_BUFFER, _offsetBuffer);
	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBuffer);
	glDrawElements(GL_TRIANGLES, _indexedData.indices.size(), GL_UNSIGNED_SHORT, (void*)0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);
	glDisableVertexAttribArray(6);
}


/* --->>> Uniforms <<<--- */
void Mesh::setMeshUniform(ShaderProgram* shaderProgram)
{
	shaderProgram->setMat4("ModelMatrix", _matrixModel);
}

void Mesh::setMatrixModel(glm::vec3 position, glm::vec3 origin, glm::vec3 rotation, glm::vec3 scale)
{
	_matrixModel = glm::mat4(1.f);
	_matrixModel = glm::translate(_matrixModel, origin);
	_matrixModel = glm::rotate(_matrixModel, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
	_matrixModel = glm::rotate(_matrixModel, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
	_matrixModel = glm::rotate(_matrixModel, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
	_matrixModel = glm::translate(_matrixModel, position - origin);
	_matrixModel = glm::scale(_matrixModel, scale);
}


/* --->>> Getters <<<--- */
glm::vec3 Mesh::getOffset()
{
	return _offset;
}

DataOBJ Mesh::getMeshData()
{
	return _meshData;
}

IndexedDataOBJ Mesh::getIndexedMeshData()
{
	return _indexedData;
}
