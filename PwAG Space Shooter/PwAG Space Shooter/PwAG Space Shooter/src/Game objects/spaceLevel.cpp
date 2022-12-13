#include "pch.h"
#include "spaceLevel.h"
#include "../Rendering system/Model/objReader.h"
#include <set>

// Initialization
SpaceLevel::SpaceLevel()
{
	this->initMaze();
}

void SpaceLevel::initMaze()
{
	this->initMazeMaterials();
	this->initMazeTextures();
	this->initObjModels();
	this->initMazeShaders();
	this->initMatrixMVP();
}

void SpaceLevel::initMazeMaterials()
{
	this->material = new Material(glm::vec3(0.25));
}

void SpaceLevel::initMazeTextures()
{
	this->torchTexture = new Texture(Texture::createTextureFromFile("res/Textures/wood.png", Texture::Type::PNG));
	this->specularMapWood = new Texture(Texture::createTextureFromFile("res/Textures/wood_specular.png", Texture::Type::SPECULAR));

	/*this->exitDoorTexture = new Texture(Texture::createTextureFromFile("res/Textures/doors.png", Texture::Type::BMP));
	this->normalMapDoors = new Texture(Texture::createTextureFromFile("res/Textures/doors_nrm.png", Texture::Type::NORMAL_MAP));
	this->specularDoors = new Texture(Texture::createTextureFromFile("res/Textures/doors_specular.png", Texture::Type::SPECULAR));*/
}

void SpaceLevel::initObjModels()
{
	std::vector<DataOBJ> torchObjects = readObj("res/Models/torch.obj");
	int torchInstances = 3;

	TransformationOBJ transformation = TransformationOBJ();

	this->player = new Player(glm::vec3(0, 0.5f, 0));
	this->startPosition = glm::vec3(0, 0.5f, 0);

	this->playerStats = new PlayerStats();

	this->pointLights.push_back(Light::Point({ 1,0,1 }, { 1,1,1 }));

	for (int i = 0; i < torchInstances; i++)
	{
		GameObject* model = new GameObject(material, this->torchTexture, torchObjects, transformation, generateOffset(0, 0, 0), 1);
		model->setSpecular(this->specularMapWood);

		Entity* entity = new Entity(model);
		entity->setPosition(glm::vec3(i, 0, i));
		entity->setDirection(glm::vec3(0, 0.2f * (i+1), 0));
		entity->setSpeed(0.2f * (i+1));
		this->torches.push_back(entity);
	}
}

std::vector<GLfloat> SpaceLevel::generateOffset(GLfloat x, GLfloat y, GLfloat z)
{
	std::vector<GLfloat> offsetsTorches;
	offsetsTorches.emplace_back(x);
	offsetsTorches.emplace_back(y);
	offsetsTorches.emplace_back(z);
	return offsetsTorches;
}

void SpaceLevel::initMazeShaders()
{
	this->fragmentShader = Shader::createShaderFromFile("Shaders/map.frag", Shader::Type::eFragment);
	this->vertexShader = Shader::createShaderFromFile("Shaders/map.vert", Shader::Type::eVertex);

	this->shaderProgram = new ShaderProgram();
	this->shaderProgram->attachShader(this->fragmentShader);
	this->shaderProgram->attachShader(this->vertexShader);
	this->shaderProgram->linkShaderProgram();

	updateLightShaders();
}

void SpaceLevel::initMatrixMVP()
{
	this->shaderProgram->useShader();
	this->player->setCameraUniforms(this->shaderProgram);
}



// Update
void SpaceLevel::updateMaze(float deltaTime)
{
	this->playerStats->reload(deltaTime);


	for (int i = 0; i < this->torches.size(); i++)
	{
		this->torches[i]->moveWithDirection(deltaTime);
	}

	pointLights[0].setPosition(this->player->getCameraPosition());

	updateLightShaders();
	// Meteor collision
}

void SpaceLevel::updateLightShaders()
{
	shaderProgram->useShader();
	setLightUniforms(*shaderProgram);
}

void SpaceLevel::setLightUniforms(ShaderProgram& shader)
{
	shader.setInt("pointLightsCount", static_cast<int>(pointLights.size()));
	char lightIndex[20];
	for (int i = 0; i < pointLights.size(); ++i)
	{
		sprintf_s(lightIndex, 20, "pointLights[%d].", i);
		std::string index{ lightIndex };
		shader.setVec3f(index + "position", pointLights[i].getPosition());
		shader.setVec3f(index + "diffuse", pointLights[i].getDiffuse());
		shader.setVec3f(index + "specular", pointLights[i].getSpecular());

		shader.setFloat(index + "constant", pointLights[i].getAttenuation().getConstant());
		shader.setFloat(index + "linear", pointLights[i].getAttenuation().getLinear());
		shader.setFloat(index + "quadratic", pointLights[i].getAttenuation().getQuadratic());
	}
}



// Render
void SpaceLevel::drawMaze(float deltaTime, bool wireframe)
{
	this->defaultRender(deltaTime);
}

void SpaceLevel::defaultRender(float deltaTime)
{
	this->shaderProgram->useShader();
	this->player->setCameraUniforms(this->shaderProgram);

	for (int i = 0; i < this->torches.size(); i++)
	{
		this->torches[i]->drawEntity(this->shaderProgram);
	}
}



// Collision
bool SpaceLevel::willBeCollisionWithExit()
{
	/*glm::vec3 playerPosition = this->player->getCameraPosition();
	bool isCollision = false;

	for (int i = 0; i < this->offsetsExitDoors.size(); i += 3)
	{
		float x = this->offsetsExitDoors[i];
		float z = this->offsetsExitDoors[i + 2];

		if (x - 1.5f < playerPosition.x &&
			x + 1.5f > playerPosition.x &&
			z - 1.5f < playerPosition.z &&
			z + 1.5f > playerPosition.z) {

			isCollision = true;
		}
	}

	return isCollision;*/
	return false;
}



// Deserialization
SpaceLevel::~SpaceLevel()
{
	delete this->player;
	delete this->shaderProgram;
	delete this->material;
}