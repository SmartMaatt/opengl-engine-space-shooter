#include "pch.h"
#include "spaceLevel.h"
#include "../Rendering system/Model/objReader.h"
#include <set>
#include <ctime>

// Initialization
SpaceLevel::SpaceLevel()
{
	this->initMaze();
}

void SpaceLevel::initMaze()
{
	srand(static_cast <unsigned> (time(0)));
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
	this->torchTexture = new Texture(Texture::createTextureFromFile("res/Textures/crystal.png", Texture::Type::PNG));
	this->specularMapWood = new Texture(Texture::createTextureFromFile("res/Textures/simple_specular.png", Texture::Type::SPECULAR));

	/*this->exitDoorTexture = new Texture(Texture::createTextureFromFile("res/Textures/doors.png", Texture::Type::BMP));
	this->normalMapDoors = new Texture(Texture::createTextureFromFile("res/Textures/doors_nrm.png", Texture::Type::NORMAL_MAP));
	this->specularDoors = new Texture(Texture::createTextureFromFile("res/Textures/doors_specular.png", Texture::Type::SPECULAR));*/
}

void SpaceLevel::initObjModels()
{
	std::vector<DataOBJ> meteosObjects = readObj("res/Models/asteroid.obj");
	TransformationOBJ transformation = TransformationOBJ();

	this->player = new Player(glm::vec3(0, 0.5f, 0));
	this->startPosition = glm::vec3(0, 0.5f, 0);

	this->playerStats = new PlayerStats();

	this->pointLights.push_back(Light::Point({ 1,0,1 }, { 1,1,1 }));

	int meteosInstances = 5;
	for (int i = 0; i < meteosInstances; i++)
	{
		GameObject* model = new GameObject(material, this->torchTexture, meteosObjects, transformation, generateOffset(0, 0, 0), 1);
		model->setSpecular(this->specularMapWood);

		Entity* entity = new Entity(model);
		entity->setName("Meteo " + std::to_string(i));

		entity->setPosition(glm::vec3(0, 0, 0));
		float size = randVal(0.1f, 0.75f);
		entity->setScale(glm::vec3(size, size, size));
		entity->setColliderRadius(size);

		entity->setDirection(glm::vec3(randVal(-1.0f, 1.0f), randVal(-1.0f, 1.0f), randVal(-1.0f, 1.0f)));
		entity->setSpeed(randVal(0.01f, 0.1f));
		this->meteos.push_back(entity);
	}
}

float SpaceLevel::randVal(float LO, float HI)
{
	return LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
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

	for (int i = 0; i < this->meteos.size(); i++)
	{
		this->meteos[i]->moveWithDirection(deltaTime);
	}

	playerToMeteoCollision();

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

	for (int i = 0; i < this->meteos.size(); i++)
	{
		this->meteos[i]->drawEntity(this->shaderProgram);
	}
}



// Collision
void SpaceLevel::playerToMeteoCollision()
{
	for (auto it = meteos.begin(); it != meteos.end();)
	{
		if (areSpheresCollided(player->getCameraPosition(), playerStats->getPlayerRadius(), (*it)->getPosition(), (*it)->getColliderRadius()))
		{
			std::cout << "Collision: Player <---> " << (*it)->getName() << std::endl;
			playerStats->takeDamage(20);
			std::cout << "Player health: " << playerStats->getHitPoints() << std::endl;
			it = meteos.erase(it);
		}
		else
		{
			++it;
		}
	}
}

bool SpaceLevel::areSpheresCollided(glm::vec3 center1, float rad1, glm::vec3 center2, float rad2)
{
	float radSum = rad1 + rad2;
	float distance = glm::distance(center1, center2);

	return (radSum > distance);
}



// Deserialization
SpaceLevel::~SpaceLevel()
{
	delete this->player;
	delete this->shaderProgram;
	delete this->material;
}