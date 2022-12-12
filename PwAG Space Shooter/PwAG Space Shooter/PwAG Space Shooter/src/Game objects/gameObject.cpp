#include "pch.h"
#include "gameObject.h"

GameObject::GameObject() {

}

GameObject::GameObject(
	Material* material,
	Texture* texture,
	std::vector<DataOBJ> mesh,
	TransformationOBJ transformation,
	std::vector<GLfloat> offsets,
	int instances) {

	this->transformation = transformation;
	this->offsets = offsets;
	this->instances = instances;

	this->material = material;
	this->texture = texture;

	if (mesh.size() > 0) {

		int size = mesh.size();

		for (int j = 0; j < size; j += 3) {

			glm::vec2& uv_0 = mesh[0 + j].uv;
			glm::vec2& uv_1 = mesh[1 + j].uv;
			glm::vec2& uv_2 = mesh[2 + j].uv;

			glm::vec3& v_0 = mesh[0 + j].vertex;
			glm::vec3& v_1 = mesh[1 + j].vertex;
			glm::vec3& v_2 = mesh[2 + j].vertex;

			glm::vec3 deltaPosition_1 = v_1 - v_0;
			glm::vec3 deltaPosition_2 = v_2 - v_0;

			glm::vec2 delta_UV_1 = uv_1 - uv_0;
			glm::vec2 delta_UV_2 = uv_2 - uv_0;

			float r = 1.0f / (delta_UV_1.x * delta_UV_2.y - delta_UV_1.y * delta_UV_2.x);
			glm::vec3 tangent = (deltaPosition_1 * delta_UV_2.y - deltaPosition_2 * delta_UV_1.y) * r;
			glm::vec3 bitangent = (deltaPosition_2 * delta_UV_1.x - deltaPosition_1 * delta_UV_2.x) * r;

			mesh[0 + j].bittangent = bitangent;
			mesh[1 + j].bittangent = bitangent;
			mesh[2 + j].bittangent = bitangent;

			mesh[0 + j].tangent = tangent;
			mesh[1 + j].tangent = tangent;
			mesh[2 + j].tangent = tangent;
		}

		this->mesh = new Mesh(mesh.data(), mesh.size(), nullptr, 0);
	}

	this->initGameObject();
}

void GameObject::initGameObject() {
	glGenVertexArrays(1, &this->mesh->VAO);
	glBindVertexArray(this->mesh->VAO);

	glGenBuffers(1, &this->mesh->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->mesh->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->mesh->verticesSize * sizeof(DataOBJ), this->mesh->vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(DataOBJ), (GLvoid*)offsetof(DataOBJ, vertex));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(DataOBJ), (GLvoid*)offsetof(DataOBJ, color));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(DataOBJ), (GLvoid*)offsetof(DataOBJ, normal));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(DataOBJ), (GLvoid*)offsetof(DataOBJ, tangent));

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(DataOBJ), (GLvoid*)offsetof(DataOBJ, bittangent));

	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(DataOBJ), (GLvoid*)offsetof(DataOBJ, uv));


	GLuint offsetBuffer;
	glGenBuffers(1, &offsetBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, offsetBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->instances * 3 * sizeof(GLfloat), &this->offsets[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(6);

	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, 0);
	glVertexAttribDivisor(6, 1);

	glBindVertexArray(0);
}

void GameObject::draw(ShaderProgram* shaderProgram) {
	shaderProgram->useShader();

	this->texture->bindTexture(0);
	if (this->specular)
	{
		this->specular->bindTexture(1);
	}

	if (this->normalMapTexture != nullptr) {
		this->normalMapTexture->bindTexture(2);
	}

	this->mesh->setMeshUniform(shaderProgram);

	this->material->setMaterialShaderUniforms(*shaderProgram);

	this->mesh->setMatrixModel(
		this->transformation.objectPosition,
		this->transformation.objectOrigin,
		this->transformation.objectRotation,
		this->transformation.objectScale);

	glBindVertexArray(this->mesh->VAO);

	glDrawArraysInstanced(GL_TRIANGLES, 0, this->mesh->verticesSize, this->instances);
}

void GameObject::setPosition(const glm::vec3 position)
{
	this->transformation.objectPosition = position;
}

void GameObject::setOrigin(const glm::vec3 origin)
{
	this->transformation.objectOrigin = origin;
}

void GameObject::setRotation(const glm::vec3 rotation)
{
	this->transformation.objectRotation = rotation;
}

void GameObject::setScale(const glm::vec3 scale)
{
	this->transformation.objectScale = scale;
}

void GameObject::setNormalMapTexture(Texture* normalMapTexture)
{
	this->normalMapTexture = normalMapTexture;
}

void GameObject::setTexture(Texture* texture)
{
	this->texture = texture;
}

void GameObject::setSpecular(Texture* texture)
{
	this->specular = texture;
}

glm::vec3 GameObject::getPosition() {
	return this->transformation.objectPosition;
}

glm::vec3 GameObject::getRotation() {
	return this->transformation.objectRotation;
}

std::vector<GLfloat> GameObject::getOffsets()
{
	return this->offsets;
}

GameObject::~GameObject()
{
	delete this->material;
	delete this->texture;
	delete this->mesh;

	if (this->normalMapTexture != nullptr) {
		delete this->normalMapTexture;
	}
}