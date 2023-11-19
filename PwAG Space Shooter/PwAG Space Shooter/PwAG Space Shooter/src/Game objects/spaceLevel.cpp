#include "pch.h"
#include "spaceLevel.h"
#include <set>
#include <ctime>

#include "../Rendering system/Model/objReader.h"
#include "../Rendering system/Model/vboIndexer.h"
#include "../SourceDep/stb_image.h"

/* --->>> Constructors / Destructor <<<--- */ 
SpaceLevel::SpaceLevel(GameState* gameState) :
	tmpDefaultFont(std::move(Font("res/Fonts/Segan.ttf", 32))),
	healthLabel(20, 50, "Health:", tmpDefaultFont), healthValueText(140, 53, "0", tmpDefaultFont),
	crystalsLabel(20, 90, "Crystals:", tmpDefaultFont), crystalsValueText(140, 93, "0", tmpDefaultFont),
	bulletLabel(20, 130, "Bullet:", tmpDefaultFont), bulletValueText(140, 130, "0", tmpDefaultFont),
	HUD("res/Textures/HUD.png", 1600, 900, 800, 450, true)
{
	this->gameState = gameState;
	this->initLevel();
}

SpaceLevel::~SpaceLevel()
{
	delete this->player;
	delete this->shaderProgram;

	// Materials
	delete this->meteorMaterialPrefab;
	delete this->crystalMaterialPrefab;
	delete this->bulletMaterialPrefab;

	// Textures
	for (size_t i = 0; i < textures.size(); i++)
	{
		delete textures[i];
	}

	// Objects
	for (size_t i = 0; i < meteors.size(); i++)
	{
		meteors[i]->destroy();
	}

	for (size_t i = 0; i < crystals.size(); i++)
	{
		crystals[i]->destroy();
	}

	if (bullet)
	{
		bullet->destroy();
	}
}


/* --->>> Getters / Setters <<<--- */
Player* SpaceLevel::getPlayer()
{
	return this->player;
}


/* --->>> Input <<<--- */
void SpaceLevel::input(float deltaTime, GameReference gameReference, Keyboard& keyboard, Mouse& mouse)
{
	player->input(gameReference, keyboard, deltaTime);

	// Shooting
	if (keyboard.keyState[static_cast<int>(Keyboard::Key::eKeyF)])
	{
		shootBullet();
	}

	// Activating HUD
	if (keyboard.keyState[static_cast<int>(Keyboard::Key::eKeyH)])
	{
		ToggleHUD();
	}
}


/* --->>> Initialization <<<--- */
void SpaceLevel::initLevel()
{
	this->initLevelMaterials();
	this->initObjModels();
	this->initLevelShaders();
	this->initMatrixMVP();
	this->initText();
}

void SpaceLevel::initLevelMaterials()
{
	Texture* meteorTexture = new Texture(Texture::createTextureFromFile("res/Textures/asteroid.png", Texture::Type::PNG));
	Texture* specularMapMeteor = new Texture(Texture::createTextureFromFile("res/Textures/asteroid_specular.png", Texture::Type::SPECULAR));
	Texture* crystalTexture = new Texture(Texture::createTextureFromFile("res/Textures/crystal.png", Texture::Type::PNG));
	Texture* specularMapCrystal = new Texture(Texture::createTextureFromFile("res/Textures/simple_specular.png", Texture::Type::SPECULAR));
	Texture* bulletTexture = new Texture(Texture::createTextureFromFile("res/Textures/sphere.png", Texture::Type::PNG));

	// To remove allocation at the end of scene
	textures.push_back(meteorTexture);
	textures.push_back(specularMapMeteor);
	textures.push_back(crystalTexture);
	textures.push_back(specularMapCrystal);
	textures.push_back(bulletTexture);

	this->meteorMaterialPrefab = new Material(meteorTexture, specularMapMeteor, nullptr, 0, 1, glm::vec3(0.1));
	this->crystalMaterialPrefab = new Material(crystalTexture, specularMapCrystal, nullptr, 0, 1, glm::vec3(0.1));
	this->bulletMaterialPrefab = new Material(bulletTexture, nullptr, nullptr, 0, 1, glm::vec3(0.25));
}

void SpaceLevel::initObjModels()
{
	// Loading data from obj
	DataOBJ meteorMeshData = readObj("res/Models/asteroid.obj");
	DataOBJ crystalMeshData = readObj("res/Models/crystal.obj");
	DataOBJ bulletMeshData = readObj("res/Models/sphere.obj");

	// Instantiating meshes prefabs
	this->meteorMeshPrefab = new Mesh(meteorMeshData, Mathf::zeroVec());
	this->crystalMeshPrefab = new Mesh(crystalMeshData, Mathf::zeroVec());
	this->bulletMeshPrefab = new Mesh(bulletMeshData, Mathf::zeroVec());

	// Player
	this->player = new Player(this->startPosition);

	// Meteors
	for (int i = 0; i < this->meteorsInstances; i++)
	{
		GameObject* model = new GameObject(new Material(*meteorMaterialPrefab), new Mesh(*meteorMeshPrefab));
		Meteor* entity = new Meteor(model, "Meteor " + std::to_string(i), this->worldRadius);
		this->meteors.push_back(entity);
	}

	// Crystals
	for (int i = 0; i < this->crystalsInstances; i++)
	{
		GameObject* model = new GameObject(new Material(*crystalMaterialPrefab), new Mesh(*crystalMeshPrefab));
		Crystal* crystal = new Crystal(model, "Crystal " + std::to_string(i), this->worldRadius);
		this->crystals.push_back(crystal);
	}
}

void SpaceLevel::initLevelShaders()
{
	this->fragmentShader = Shader::createShaderFromFile("Shaders/map.frag", Shader::Type::eFragment);
	this->vertexShader = Shader::createShaderFromFile("Shaders/map.vert", Shader::Type::eVertex);

	this->shaderProgram = new ShaderLightProgram();
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


/* --->>> Update <<<--- */
void SpaceLevel::update(float deltaTime)
{
	updatePlayer(deltaTime);
	updateMeteors(deltaTime);
	updateCrystals(deltaTime);
	updateBullet(deltaTime);

	updateLightShaders();
	updateGuiTexts();

	updateOutcomes();
}

void SpaceLevel::updatePlayer(float deltaTime)
{
	player->update(deltaTime);

	// Square border holder ;)
	glm::vec3 playerPos = this->player->getCameraPosition();
	if (playerPos.x > this->worldRadius) { this->player->setCameraPosition(glm::vec3(this->worldRadius, playerPos.y, playerPos.z)); }
	if (playerPos.y > this->worldRadius) { this->player->setCameraPosition(glm::vec3(playerPos.x, this->worldRadius, playerPos.z)); }
	if (playerPos.z > this->worldRadius) { this->player->setCameraPosition(glm::vec3(playerPos.x, playerPos.y, this->worldRadius)); }
	if (playerPos.x < -this->worldRadius) { this->player->setCameraPosition(glm::vec3(-this->worldRadius, playerPos.y, playerPos.z)); }
	if (playerPos.y < -this->worldRadius) { this->player->setCameraPosition(glm::vec3(playerPos.x, -this->worldRadius, playerPos.z)); }
	if (playerPos.z < -this->worldRadius) { this->player->setCameraPosition(glm::vec3(playerPos.x, playerPos.y, -this->worldRadius)); }

	// Player stats
	this->player->getStats()->reloadBullet(deltaTime);
}

void SpaceLevel::updateMeteors(float deltaTime)
{
	// Meteors
	for (auto meteor = meteors.begin(); meteor != meteors.end();)
	{
		// Update
		(*meteor)->update(deltaTime);
		
		// >>> Collisions <<<
		collideMeteor(meteor);
	}
}

void SpaceLevel::updateCrystals(float deltaTime)
{
	// Crystals
	for (auto crystal = crystals.begin(); crystal != crystals.end();)
	{
		// Update
		(*crystal)->update(deltaTime);

		// >>> Collisions <<<
		collideCrystal(crystal);
	}
}

void SpaceLevel::updateBullet(float deltaTime)
{
	// Bullet
	if (bullet)
	{
		if (bullet->isDead())
		{
			// Kill
			delete bullet;
			bullet = nullptr;
		}
		else
		{
			// Update
			bullet->update(deltaTime);
		}
	}
}

void SpaceLevel::updateLightShaders()
{
	shaderProgram->useShader();
	setLightUniforms(*shaderProgram);
}

void SpaceLevel::updateGuiTexts()
{
#ifndef DIST
	PlayerStats* stats = player->getStats();

	// Health info
	std::stringstream streamForHealth;
	streamForHealth << std::fixed << std::setprecision(4);
	streamForHealth << stats->getHitPoints() << "/" << stats->getMaxHitPoints();
	healthValueText.setText(streamForHealth.str());

	// Points info
	std::stringstream streamForCrystals;
	streamForCrystals << std::fixed << std::setprecision(4);
	streamForCrystals << stats->getPoints() << "/" << crystalsInstances;
	crystalsValueText.setText(streamForCrystals.str());

	// Shooting info
	if (stats->canIShoot())
	{
		bulletLabel.setText("Bullet:");
		bulletValueText.setText("loaded!");
	}
	else
	{
		std::stringstream streamForBullet;
		streamForBullet << std::fixed << std::setprecision(2);
		streamForBullet << stats->getReloadTime() << "/" << stats->getReloadMaxTime();
		bulletLabel.setText("Loading:");
		bulletValueText.setText(streamForBullet.str());
	}
#endif
}

void SpaceLevel::updateOutcomes()
{
	// Outcomes
	if (crystalsInstances == player->getStats()->getPoints())
	{
		this->gameState->winLevel();
	}

	if (player->getStats()->getHitPoints() == 0)
	{
		this->gameState->looseLevel();
	}
}


/* --->>> Collisions <<<--- */
void SpaceLevel::collideMeteor(std::vector<Meteor*>::iterator& meteor)
{
	// Meteor <-> World border
	if (glm::distance((*meteor)->getPosition(), Mathf::zeroVec()) > this->worldRadius)
	{
		(*meteor)->changeDirectionOnCollision();
	}

	// Meteor <-> Player
	PlayerStats* stats = player->getStats();
	if (Mathf::areSpheresCollided(player->getCameraPosition(), stats->getPlayerRadius(), (*meteor)->getPosition(), (*meteor)->getColliderRadius()))
	{
		stats->takeDamage(20);

		std::cout << "Collision: Player <---> " << (*meteor)->getName() << std::endl;
		std::cout << "Player health: " << stats->getHitPoints() << std::endl;

		(*meteor)->destroy();
		meteor = meteors.erase(meteor);
	}
	// Meteor <-> Bullet
	else if (bullet && !bullet->isDead() && Mathf::areSpheresCollided(bullet->getPosition(), bullet->getColliderRadius(), (*meteor)->getPosition(), (*meteor)->getColliderRadius()))
	{
		std::cout << "Collision: Bullet <---> " << (*meteor)->getName() << std::endl;
		(*meteor)->destroy();
		bullet->destroy();

		meteor = meteors.erase(meteor);
		bullet = nullptr;
	}
	else { ++meteor; }
}

void SpaceLevel::collideCrystal(std::vector<Crystal*>::iterator& crystal)
{
	// Crystal <-> Player
	PlayerStats* stats = player->getStats();
	if (Mathf::areSpheresCollided(player->getCameraPosition(), stats->getPlayerRadius(), (*crystal)->getPosition(), (*crystal)->getColliderRadius()))
	{
		stats->addPoint();

		std::cout << "Collision: Player <---> " << (*crystal)->getName() << std::endl;

		(*crystal)->destroy();
		crystal = crystals.erase(crystal);
	}
	else { ++crystal; }
}


/* --->>> Lights <<<--- */
void SpaceLevel::setLightUniforms(ShaderLightProgram& shaderProgram)
{
	int playerLights = 1;
	int bulletLights = 0;
	if (bullet) { bulletLights = 1; }

	shaderProgram.setNumberOfLights(playerLights + crystals.size() + bulletLights);
	char lightIndex[20];

	// Default lights
	sprintf_s(lightIndex, 20, "pointLights[%d].", 0);
	std::string index { lightIndex };
	shaderProgram.setLightUniforms(*(player->getLight()), index);

	// Crystals lights
	for (int i = playerLights; i < crystals.size() + playerLights; i++)
	{
		sprintf_s(lightIndex, 20, "pointLights[%d].", i);
		std::string index { lightIndex };

		int objIndex = i - 1;
		shaderProgram.setLightUniforms(*(crystals[objIndex]->light), index);
	}

	// Bullet lights
	if (bullet && !bullet->isDead())
	{
		sprintf_s(lightIndex, 20, "pointLights[%d].", playerLights + crystals.size());
		std::string index{ lightIndex };
		shaderProgram.setLightUniforms(*(bullet->light), index);
	}
}


/* --->>> Render <<<--- */
void SpaceLevel::draw(float deltaTime, bool wireframe)
{
	this->shaderProgram->useShader();
	this->player->setCameraUniforms(this->shaderProgram);

	for (int i = 0; i < this->meteors.size(); i++)
	{
		this->meteors[i]->draw(this->shaderProgram);
	}

	for (int i = 0; i < this->crystals.size(); i++)
	{
		this->crystals[i]->draw(this->shaderProgram);
	}

	if (bullet && !bullet->isDead())
	{
		this->bullet->draw(this->shaderProgram);
	}
	drawGui();
}


/* --->>> GUI <<<--- */
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


/* --->>> Shooting <<<--- */
void SpaceLevel::shootBullet()
{
	PlayerStats* stats = player->getStats();
	if (stats->canIShoot())
	{
		// Bullet spawn
		this->bullet = spawnBullet();
		stats->shoot();
	}
	else
	{
		std::cout << "Can't shoot bullet" << std::endl;
	}
}

Bullet* SpaceLevel::spawnBullet()
{
	GameObject* model = new GameObject(new Material(*bulletMaterialPrefab), new Mesh(*bulletMeshPrefab));
	Bullet* bullet = new Bullet(model, "Bullet", 7, this->player);
	return bullet;
}