#include "pch.h"
#include "spaceLevel.h"
#include "../Rendering system/Model/objReader.h"
#include <set>
#include <ctime>

// Initialization
SpaceLevel::SpaceLevel()
{
	this->initLevel();
}

void SpaceLevel::initLevel()
{
	srand(static_cast <unsigned> (time(0)));
	this->initLevelMaterials();
	this->initLevelTextures();
	this->initObjModels();
	this->initLevelShaders();
	this->initMatrixMVP();
}

void SpaceLevel::initLevelMaterials()
{
	this->material = new Material(glm::vec3(0.25));
}

void SpaceLevel::initLevelTextures()
{
	this->meteorTexture = new Texture(Texture::createTextureFromFile("res/Textures/asteroid.png", Texture::Type::PNG));
	this->specularMapMeteor = new Texture(Texture::createTextureFromFile("res/Textures/asteroid_specular.png", Texture::Type::SPECULAR));
	
	this->crystalTexture = new Texture(Texture::createTextureFromFile("res/Textures/crystal.png", Texture::Type::PNG));
	this->specularMapCrystal = new Texture(Texture::createTextureFromFile("res/Textures/simple_specular.png", Texture::Type::SPECULAR));
}

void SpaceLevel::initObjModels()
{
	std::vector<DataOBJ> meteorsObjects = readObj("res/Models/asteroid.obj");
	std::vector<DataOBJ> crystalsObjects = readObj("res/Models/crystal.obj");
	TransformationOBJ transformation = TransformationOBJ();

	// Player
	this->player = new Player(glm::vec3(0, 0.5f, 0));
	this->startPosition = glm::vec3(0, 0.5f, 0);
	this->playerStats = new PlayerStats();

	// Light source
	this->pointLights.push_back(Light::Point({ 1,0,1 }, { 1,1,1 }));

	// Meteors
	for (int i = 0; i < this->meteorsInstances; i++)
	{
		GameObject* model = new GameObject(material, this->meteorTexture, meteorsObjects, transformation, generateOffset(0, 0, 0), 1);
		model->setSpecular(this->specularMapMeteor);

		Entity* entity = new Entity(model);
		entity->setName("Meteo " + std::to_string(i));

		entity->setPosition(randCoordsInSphere(this->worldRadius));
		float size = randVal(0.1f, 0.75f);
		entity->setScale(glm::vec3(size, size, size));
		entity->setColliderRadius(size);

		entity->setDirection(glm::vec3(randVal(-1.0f, 1.0f), randVal(-1.0f, 1.0f), randVal(-1.0f, 1.0f)));
		entity->setSpeed(randVal(0.3f, 0.7f));
		this->meteors.push_back(entity);
	}

	// Crystals
	for (int i = 0; i < this->crystalsInstances; i++)
	{
		GameObject* model = new GameObject(material, this->crystalTexture, crystalsObjects, transformation, generateOffset(0, 0, 0), 1);
		model->setSpecular(this->specularMapCrystal);

		Crystal* crystal = new Crystal(model);
		crystal->setName("Crystal " + std::to_string(i));

		crystal->setRotation(glm::vec3(-90, 0, 0));
		crystal->setPosition(randCoordsInSphere(this->worldRadius));
		crystal->setOrigin(crystal->getPosition());
		crystal->setScale(this->one * 0.05f);
		crystal->setColliderRadius(0.5f);

		crystal->light = new Light::Point(crystal->getPosition(), { 1,0,0 });
		this->crystals.push_back(crystal);
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

void SpaceLevel::initLevelShaders()
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



// Randomize
float SpaceLevel::randVal(float LO, float HI)
{
	return LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
}

glm::vec3 SpaceLevel::randCoordsInSphere(float radius)
{
	float x = randVal(-1, 1);
	float y = randVal(-1, 1);
	float z = randVal(-1, 1);

	float mag = glm::sqrt((x * x) + (y * y) + (z * z));
	float d = randVal(0, radius) / mag;

	x *= d;
	y *= d;
	z *= d;
	return glm::vec3(x, y, z);
}



// Update
void SpaceLevel::updateLevel(float deltaTime)
{
	// Player
	// Square border holder ;)
	glm::vec3 playerPos = this->player->getCameraPosition();
	if (playerPos.x > this->worldRadius) { this->player->setCameraPosition(glm::vec3(this->worldRadius, playerPos.y, playerPos.z)); }
	if (playerPos.y > this->worldRadius) { this->player->setCameraPosition(glm::vec3(playerPos.x, this->worldRadius, playerPos.z)); }
	if (playerPos.z > this->worldRadius) { this->player->setCameraPosition(glm::vec3(playerPos.x, playerPos.y, this->worldRadius)); }
	if (playerPos.x < -this->worldRadius) { this->player->setCameraPosition(glm::vec3(-this->worldRadius, playerPos.y, playerPos.z)); }
	if (playerPos.y < -this->worldRadius) { this->player->setCameraPosition(glm::vec3(playerPos.x, -this->worldRadius, playerPos.z)); }
	if (playerPos.z < -this->worldRadius) { this->player->setCameraPosition(glm::vec3(playerPos.x, playerPos.y, -this->worldRadius)); }

	// Player stats
	this->playerStats->reload(deltaTime);

	// Meteors
	for (auto it = meteors.begin(); it != meteors.end();)
	{
		// Move
		(*it)->moveWithDirection(deltaTime);

		// World border
		if (glm::distance((*it)->getPosition(), this->zero) > this->worldRadius)
		{
			(*it)->setDirection(glm::vec3(randVal(-1.0f, 1.0f), randVal(-1.0f, 1.0f), randVal(-1.0f, 1.0f)));
			// std::cout << this->meteors[i]->getName() << " changed direction!" << std::endl;
		}

		// Meteor - player collision
		if (areSpheresCollided(player->getCameraPosition(), playerStats->getPlayerRadius(), (*it)->getPosition(), (*it)->getColliderRadius()))
		{
			std::cout << "Collision: Player <---> " << (*it)->getName() << std::endl;
			playerStats->takeDamage(20);
			std::cout << "Player health: " << playerStats->getHitPoints() << std::endl;
			it = meteors.erase(it);
		}
		else { ++it; }
	}

	// Crystals
	for (auto it = crystals.begin(); it != crystals.end();)
	{
		// Rotation
		glm::vec3 newRotation = (*it)->getRotation() + glm::vec3(0, 0, 6.28f) * deltaTime;
		(*it)->setRotation(newRotation);

		// Crystal - player collision
		if (areSpheresCollided(player->getCameraPosition(), playerStats->getPlayerRadius(), (*it)->getPosition(), (*it)->getColliderRadius()))
		{
			std::cout << "Collision: Player <---> " << (*it)->getName() << std::endl;
			it = crystals.erase(it);
		}
		else { ++it; }
	}

	pointLights[0].setPosition(this->player->getCameraPosition());
	updateLightShaders();
}

void SpaceLevel::updateLightShaders()
{
	shaderProgram->useShader();
	setLightUniforms(*shaderProgram);
}

void SpaceLevel::setLightUniforms(ShaderProgram& shader)
{
	shader.setInt("pointLightsCount", static_cast<int>(pointLights.size() + crystals.size()));
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

	for (int i = pointLights.size(); i < crystals.size() + pointLights.size(); i++)
	{
		sprintf_s(lightIndex, 20, "pointLights[%d].", i);
		std::string index{ lightIndex };
		int objIndex = i - pointLights.size();

		shader.setVec3f(index + "position", crystals[objIndex]->light->getPosition());
		shader.setVec3f(index + "diffuse", crystals[objIndex]->light->getDiffuse());
		shader.setVec3f(index + "specular", crystals[objIndex]->light->getSpecular());

		shader.setFloat(index + "constant", crystals[objIndex]->light->getAttenuation().getConstant());
		shader.setFloat(index + "linear", crystals[objIndex]->light->getAttenuation().getLinear());
		shader.setFloat(index + "quadratic", crystals[objIndex]->light->getAttenuation().getQuadratic());
	}
}



// Render
void SpaceLevel::drawLevel(float deltaTime, bool wireframe)
{
	this->shaderProgram->useShader();
	this->player->setCameraUniforms(this->shaderProgram);

	for (int i = 0; i < this->meteors.size(); i++)
	{
		this->meteors[i]->drawEntity(this->shaderProgram);
	}

	for (int i = 0; i < this->crystals.size(); i++)
	{
		this->crystals[i]->drawEntity(this->shaderProgram);
	}
}



// Collision
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