#include "pch.h"
#include "spaceLevel.h"
#include <set>
#include <ctime>

#include "../Rendering system/Model/objReader.h"
#include "../Rendering system/Model/vboIndexer.h"
#include "../SourceDep/stb_image.h"

// Initialization
SpaceLevel::SpaceLevel() :
	tmpDefaultFont(std::move(Font("res/Fonts/Segan.ttf", 32))),
	healthLabel(20, 50, "Health:", tmpDefaultFont), healthValueText(140, 53, "0", tmpDefaultFont),
	crystalsLabel(20, 90, "Crystals:", tmpDefaultFont), crystalsValueText(140, 93, "0", tmpDefaultFont),
	bulletLabel(20, 130, "Bullet:", tmpDefaultFont), bulletValueText(140, 130, "0", tmpDefaultFont),
	HUD("res/Textures/HUD.png", 1600, 900, 800, 450, true)
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
	this->initText();
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

	this->bulletTexture = new Texture(Texture::createTextureFromFile("res/Textures/sphere.png", Texture::Type::PNG));
}

void SpaceLevel::initObjModels()
{
	DataOBJ meteorsObjects = readObj("res/Models/asteroid.obj");
	DataOBJ crystalsObjects = readObj("res/Models/crystal.obj");
	DataOBJ bulletObjects = readObj("res/Models/sphere.obj");

	IndexedDataOBJ meteorsIndexedObjects = indexVBO_TBN(meteorsObjects);
	IndexedDataOBJ crystalsIndexedObjects = indexVBO_TBN(crystalsObjects);
	this->indexedBulletObjects = indexVBO_TBN(bulletObjects);

	// Player
	this->player = new Player(glm::vec3(0, 0.5f, 0));
	this->startPosition = glm::vec3(0, 0.5f, 0);
	this->playerStats = new PlayerStats();

	// Light source
	this->pointLights.push_back(Light::Point({ 1,0,1 }, { 1,1,1 }));

	// Meteors
	for (int i = 0; i < this->meteorsInstances; i++)
	{
		GameObject* model = new GameObject(material, this->meteorTexture, meteorsIndexedObjects, this->zero, 1);
		model->setSpecular(this->specularMapMeteor);

		Entity* entity = new Entity(model);
		entity->setName("Meteo " + std::to_string(i));

		entity->setPosition(randCoordsInSphere(this->worldRadius / 2));
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
		GameObject* model = new GameObject(material, this->crystalTexture, crystalsIndexedObjects, this->zero, 1);
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

void SpaceLevel::initText()
{
	// Gui text shader initialization
	Shader textVert = Shader::createShaderFromFile("Shaders/text.vert", Shader::Type::eVertex);
	Shader textFrag = Shader::createShaderFromFile("Shaders/text.frag", Shader::Type::eFragment);

	textShader.attachShader(textVert);
	textShader.attachShader(textFrag);
	textShader.linkShaderProgram();

	// Gui text color
	healthLabel.setColor(glm::vec3(1, 1, 1));
	healthValueText.setColor(glm::vec3(1, 1, 1));	
	
	crystalsLabel.setColor(glm::vec3(1, 0, 0));
	crystalsValueText.setColor(glm::vec3(1, 0, 0));

	bulletLabel.setColor(glm::vec3(0, 0, 1));
	bulletValueText.setColor(glm::vec3(0, 0, 1));
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
	updatePlayer(deltaTime);
	updateMeteors(deltaTime);
	updateCrystals(deltaTime);
	updateBullet(deltaTime);

	pointLights[0].setPosition(this->player->getCameraPosition());
	updateLightShaders();
	updateTextValues();
}

void SpaceLevel::updatePlayer(float deltaTime)
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
	this->playerStats->reloadBullet(deltaTime);
}

void SpaceLevel::updateMeteors(float deltaTime)
{
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
			delete (*it);
			it = meteors.erase(it);
		}
		else { ++it; }
	}
}

void SpaceLevel::updateCrystals(float deltaTime)
{
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
			delete (*it);
			it = crystals.erase(it);
			this->playerStats->addPoint();
		}
		else { ++it; }
	}
}

void SpaceLevel::updateBullet(float deltaTime)
{
	// Bullet
	if (bullet != nullptr)
	{
		bullet->moveWithDirection(deltaTime);
		bullet->light->setPosition(bullet->getPosition());

		// Bullet death
		bullet->calcAge(deltaTime);
		if (bullet->isDead())
		{
			delete bullet;
			bullet = nullptr;
			std::cout << "Erased bullet" << std::endl;
			return;
		}

		for (auto it = meteors.begin(); it != meteors.end();)
		{
			// Meteor - bullet collision
			if (areSpheresCollided(bullet->getPosition(), bullet->getColliderRadius(), (*it)->getPosition(), (*it)->getColliderRadius()))
			{
				std::cout << "Collision: Bullet <---> " << (*it)->getName() << std::endl;
				delete (*it);
				delete bullet;

				it = meteors.erase(it);
				bullet = nullptr;
				return;
			}
			else { ++it; }
		}
	}
}

void SpaceLevel::updateLightShaders()
{
	shaderProgram->useShader();
	setLightUniforms(*shaderProgram);
}

void SpaceLevel::setLightUniforms(ShaderProgram& shader)
{
	int includeBullet = 0;
	if (bullet != nullptr) { includeBullet = 1; }

	shader.setInt("pointLightsCount", static_cast<int>(pointLights.size() + crystals.size() + includeBullet));
	char lightIndex[20];

	// Default lights
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

	// Crystals lights
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

	// Bullet lights
	if (bullet != nullptr)
	{
		sprintf_s(lightIndex, 20, "pointLights[%d].", pointLights.size() + crystals.size());
		std::string index{ lightIndex };

		shader.setVec3f(index + "position", bullet->light->getPosition());
		shader.setVec3f(index + "diffuse", bullet->light->getDiffuse());
		shader.setVec3f(index + "specular", bullet->light->getSpecular());

		shader.setFloat(index + "constant", bullet->light->getAttenuation().getConstant());
		shader.setFloat(index + "linear", bullet->light->getAttenuation().getLinear());
		shader.setFloat(index + "quadratic", bullet->light->getAttenuation().getQuadratic());
	}
}

void SpaceLevel::updateTextValues()
{
#ifndef DIST
	std::stringstream streamForHealth;
	streamForHealth << std::fixed << std::setprecision(4);
	streamForHealth << playerStats->getHitPoints() << "/" << playerStats->getMaxHitPoints();
	healthValueText.setText(streamForHealth.str());

	std::stringstream streamForCrystals;
	streamForCrystals << std::fixed << std::setprecision(4);
	streamForCrystals << playerStats->getPoints() << "/" << crystalsInstances;
	crystalsValueText.setText(streamForCrystals.str());

	if (playerStats->canIShoot())
	{
		bulletLabel.setText("Bullet:");
		bulletValueText.setText("loaded!");
	}
	else
	{
		std::stringstream streamForBullet;
		streamForBullet << std::fixed << std::setprecision(2);
		streamForBullet << playerStats->getReloadTime() << "/" << playerStats->getReloadMaxTime();
		bulletLabel.setText("Loading:");
		bulletValueText.setText(streamForBullet.str());
	}
#endif
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

	if (bullet != nullptr)
	{
		this->bullet->drawEntity(this->shaderProgram);
	}

	drawGui();
}

void SpaceLevel::drawGui() 
{
	if (hudActivated)
	{
		HUD.Draw();
	}

#ifndef DIST
	textShader.useShader();
	auto projection = glm::ortho(0.0f, static_cast<float>(Config::g_defaultWidth), 0.0f, static_cast<float>(Config::g_defaultHeight));
	textShader.setMat4("MVP", projection);

	healthLabel.render(textShader);
	healthValueText.render(textShader);

	crystalsLabel.render(textShader);
	crystalsValueText.render(textShader);

	bulletLabel.render(textShader);
	bulletValueText.render(textShader);
#endif

	if (hudChangeLatch > 0)
		hudChangeLatch--;
}

void SpaceLevel::ToggleHUD()
{
	if (!(hudChangeLatch > 0))
	{
		hudActivated = !hudActivated;
		hudChangeLatch = 10;
	}
}





// Collision
bool SpaceLevel::areSpheresCollided(glm::vec3 center1, float rad1, glm::vec3 center2, float rad2)
{
	float radSum = rad1 + rad2;
	float distance = glm::distance(center1, center2);

	return (radSum > distance);
}




// Shooting
void SpaceLevel::shootBullet()
{
	if (this->playerStats->canIShoot())
	{
		// Bullet spawn
		this->bullet = spawnBullet();
		this->playerStats->shoot();
	}
	else
	{
		std::cout << "Can't shoot bullet" << std::endl;
	}
}

Bullet* SpaceLevel::spawnBullet()
{
	GameObject* model = new GameObject(new Material(glm::vec3(0.25)), this->bulletTexture, this->indexedBulletObjects, this->zero, 1);

	Bullet* bullet = new Bullet(model, 7);
	bullet->setName("Bullet");

	bullet->setPosition(this->player->getCameraPosition() + this->player->getDirection() * 0.3f);
	bullet->setOrigin(this->player->getCameraPosition());
	bullet->setScale(this->one * 0.05f);

	bullet->setDirection(this->player->getDirection());
	bullet->setSpeed(5);
	bullet->setColliderRadius(0.5f);

	bullet->light = new Light::Point(bullet->getPosition(), { 0,0,1 });
	return bullet;
}




// Deserialization
SpaceLevel::~SpaceLevel()
{
	delete this->player;
	delete this->shaderProgram;
	delete this->material;

	for (size_t i = 0; i < meteors.size(); i++)
	{
		delete meteors[i];
	}

	for (size_t i = 0; i < crystals.size(); i++)
	{
		delete crystals[i];
	}

	delete this->meteorTexture;
	delete this->specularMapMeteor;
	delete this->crystalTexture;
	delete this->specularMapCrystal;
	delete this->bulletTexture;
}