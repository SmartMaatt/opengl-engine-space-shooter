#include "pch.h"
#include "gameObject.h"

/* --->>> Constructors / Destructor <<<--- */
GameObject::GameObject() {}
GameObject::GameObject(Material* material, Mesh* mesh)
{
	_material = material;
	_mesh = mesh;
}

GameObject::~GameObject()
{
	if (_material)
	{
		delete _material;
		_material = nullptr;
	}

	if (_mesh)
	{
		delete _mesh;
		_mesh = nullptr;
	}
}


/* --->>> Drawing <<<--- */
void GameObject::draw(ShaderProgram* shaderProgram)
{
	// Use shader
	shaderProgram->useShader();

	// Binding textures
	_material->bindTextures();

	// Setting uniforms
	_mesh->setMeshUniform(shaderProgram);
	_material->setMaterialShaderUniforms(*shaderProgram);

	_mesh->setMatrixModel(
		_transformation.objectPosition,
		_transformation.objectOrigin,
		_transformation.objectRotation,
		_transformation.objectScale
	);

	// Shader per vertex values
	_mesh->drawMesh();
}


/* --->>> Getters / Setters <<<--- */
void GameObject::setPosition(const glm::vec3 _position)
{
	_transformation.objectPosition = _position;
}

void GameObject::setOrigin(const glm::vec3 origin)
{
	_transformation.objectOrigin = origin;
}

void GameObject::setRotation(const glm::vec3 rotation)
{
	_transformation.objectRotation = rotation;
}

void GameObject::setScale(const glm::vec3 scale)
{
	_transformation.objectScale = scale;
}

glm::vec3 GameObject::getPosition()
{
	return _transformation.objectPosition;
}

glm::vec3 GameObject::getRotation()
{
	return _transformation.objectRotation;
}