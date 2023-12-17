#include "pch.h"
#include "spaceLevel.h"
#include <set>
#include <ctime>

#include "../Rendering system/Model/objReader.h"
#include "../Rendering system/Model/vboIndexer.h"
#include "../SourceDep/stb_image.h"

/* --->>> Constructors / Destructor <<<--- */
SpaceLevel::SpaceLevel(GameState* gameState, int levelNumber) :
	_tmpDefaultFont(std::move(Font("res/Fonts/Segan.ttf", 32))),
	_healthLabel(20, 50, "Health:", _tmpDefaultFont), _healthValueText(140, 53, "0", _tmpDefaultFont),
	_crystalsLabel(20, 90, "Crystals:", _tmpDefaultFont), _crystalsValueText(140, 93, "0", _tmpDefaultFont),
	_bulletLabel(20, 130, "Bullet:", _tmpDefaultFont), _bulletValueText(140, 130, "0", _tmpDefaultFont),
	_HUD("res/Textures/HUD.png", 1600, 900, 800, 450, true)
{
	levelFileReader = SpaceLevelFileReader();
	levelFileReader.loadFile();
	GameLevel levelInfo = GameLevel(levelFileReader.getLevelInfo(levelNumber));
	levelID = levelNumber;
	enemiesInstances = levelInfo.enemiesCount;
	enemiesBulletShootInterval.first = levelInfo.enemiesBulletShootIntervalMin;
	enemiesBulletShootInterval.second = levelInfo.enemiesBulletShootIntervalMax;
	playerShootTimeot = levelInfo.playerShootTimeot;
	medkitsInstances = levelInfo.medkitsCount;
	_gameState = gameState;
	_initLevel();
}

SpaceLevel::~SpaceLevel()
{
	delete _player;
	delete _shaderProgram;
	delete _textShader;
	delete _skybox;

	// Materials
	delete _alienMaterialPrefab;
	delete _meteorMaterialPrefab;
	delete _crystalMaterialPrefab;
	delete _bulletMaterialPrefab;

	// Textures
	for (size_t i = 0; i < _textures.size(); i++)
	{
		delete _textures[i];
	}

	// Objects
	for (size_t i = 0; i < _aliens.size(); i++)
	{
		_aliens[i]->destroy();
	}

	for (size_t i = 0; i < _meteors.size(); i++)
	{
		_meteors[i]->destroy();
	}

	for (size_t i = 0; i < _crystals.size(); i++)
	{
		_crystals[i]->destroy();
	}

	if (_bullet)
	{
		_bullet->destroy();
	}
}


/* --->>> Input <<<--- */
void SpaceLevel::input(float deltaTime, GameReference gameReference, Keyboard& keyboard, Mouse& mouse)
{
	_player->input(gameReference, keyboard, deltaTime);

	// Shooting
	if (keyboard.keyState[static_cast<int>(Keyboard::Key::eKeyF)])
	{
		_shootBullet();
	}

	// Activating HUD
	if (keyboard.keyState[static_cast<int>(Keyboard::Key::eKeyH)])
	{
		_toggleHUD();
	}
}


/* --->>> Initialization <<<--- */
void SpaceLevel::_initLevel()
{
	_initLevelMaterials();
	_initObjModels();
	_initLevelShaders();
	_initMatrixMVP();
	_initText();
}

void SpaceLevel::_initLevelMaterials()
{
	Texture* alienTexture = new Texture(Texture::createTextureFromFile("res/Textures/Alien/AlienFighterGreen_AlbedoTransparency.png", Texture::Type::PNG));
	Texture* alienSpecular = new Texture(Texture::createTextureFromFile("res/Textures/Alien/AlienFighter_Emission.png", Texture::Type::SPECULAR));
	Texture* alienNormal = new Texture(Texture::createTextureFromFile("res/Textures/Alien/AlienFighter_Normal.png", Texture::Type::G_BUFFER_NORMAL));

	Texture* meteorTexture = new Texture(Texture::createTextureFromFile("res/Textures/asteroid.png", Texture::Type::PNG));
	Texture* meteorSpecular = new Texture(Texture::createTextureFromFile("res/Textures/asteroid_specular.png", Texture::Type::SPECULAR));
	Texture* crystalTexture = new Texture(Texture::createTextureFromFile("res/Textures/crystal.png", Texture::Type::PNG));
	Texture* crystalSpecular = new Texture(Texture::createTextureFromFile("res/Textures/simple_specular.png", Texture::Type::SPECULAR));
	Texture* bulletTexture = new Texture(Texture::createTextureFromFile("res/Textures/sphere.png", Texture::Type::PNG));

	// To remove allocation at the end of scene
	_textures.push_back(alienTexture);
	_textures.push_back(alienSpecular);
	_textures.push_back(alienNormal);
	_textures.push_back(meteorTexture);
	_textures.push_back(meteorSpecular);
	_textures.push_back(crystalTexture);
	_textures.push_back(crystalSpecular);
	_textures.push_back(bulletTexture);

	_alienMaterialPrefab = new Material(alienTexture, alienSpecular, nullptr, 0, 1, glm::vec3(0.1));
	_meteorMaterialPrefab = new Material(meteorTexture, meteorSpecular, nullptr, 0, 1, glm::vec3(0.1));
	_crystalMaterialPrefab = new Material(crystalTexture, crystalSpecular, nullptr, 0, 1, glm::vec3(0.1));
	_bulletMaterialPrefab = new Material(bulletTexture, nullptr, nullptr, 0, 1, glm::vec3(0.25));
}

void SpaceLevel::_initObjModels()
{
	// Loading data from obj
	DataOBJ alienMeshData = readObj("res/Models/alien.obj");
	DataOBJ meteorMeshData = readObj("res/Models/asteroid.obj");
	DataOBJ crystalMeshData = readObj("res/Models/crystal.obj");
	DataOBJ bulletMeshData = readObj("res/Models/sphere.obj");

	// Instantiating meshes prefabs
	_alienMeshPrefab = new Mesh(alienMeshData, Mathf::zeroVec());
	_meteorMeshPrefab = new Mesh(meteorMeshData, Mathf::zeroVec());
	_crystalMeshPrefab = new Mesh(crystalMeshData, Mathf::zeroVec());
	_bulletMeshPrefab = new Mesh(bulletMeshData, Mathf::zeroVec());

	// Player
	_player = new Player(startPosition);

	// Aliens
	for (int i = 0; i < enemiesInstances; i++)
	{
		GameObject* model = new GameObject(new Material(*_alienMaterialPrefab), new Mesh(*_alienMeshPrefab));
		Alien* alien = new Alien(model, "Alien " + std::to_string(i), worldRadius);
		_aliens.push_back(alien);
	}

	// Meteors
	for (int i = 0; i < meteorsInstances; i++)
	{
		GameObject* model = new GameObject(new Material(*_meteorMaterialPrefab), new Mesh(*_meteorMeshPrefab));
		Meteor* entity = new Meteor(model, "Meteor " + std::to_string(i), worldRadius);
		_meteors.push_back(entity);
	}

	// Crystals
	for (int i = 0; i < crystalsInstances; i++)
	{
		GameObject* model = new GameObject(new Material(*_crystalMaterialPrefab), new Mesh(*_crystalMeshPrefab));
		Crystal* crystal = new Crystal(model, "Crystal " + std::to_string(i), worldRadius);
		_crystals.push_back(crystal);
	}
}

void SpaceLevel::_initLevelShaders()
{
	// Main shader
	_fragmentShader = Shader::createShaderFromFile("shaders/map.frag", Shader::Type::eFragment);
	_vertexShader = Shader::createShaderFromFile("shaders/map.vert", Shader::Type::eVertex);

	_shaderProgram = new ShaderLightProgram();
	_shaderProgram->attachShader(_fragmentShader);
	_shaderProgram->attachShader(_vertexShader);
	_shaderProgram->linkShaderProgram();

	_updateLightShaders();

	// Skybox shader
	_skybox = new Skybox(facesCubemap);

	// Gui shader
	Shader textVert = Shader::createShaderFromFile("shaders/text.vert", Shader::Type::eVertex);
	Shader textFrag = Shader::createShaderFromFile("shaders/text.frag", Shader::Type::eFragment);

	_textShader = new ShaderProgram();
	_textShader->attachShader(textVert);
	_textShader->attachShader(textFrag);
	_textShader->linkShaderProgram();
}

void SpaceLevel::_initMatrixMVP()
{
	_shaderProgram->useShader();
	_player->setCameraUniforms(_shaderProgram);
}

void SpaceLevel::_initText()
{
	// Gui text color
	_healthLabel.setColor(glm::vec3(1, 1, 1));
	_healthValueText.setColor(glm::vec3(1, 1, 1));

	_crystalsLabel.setColor(glm::vec3(1, 0, 0));
	_crystalsValueText.setColor(glm::vec3(1, 0, 0));

	_bulletLabel.setColor(glm::vec3(0, 0, 1));
	_bulletValueText.setColor(glm::vec3(0, 0, 1));
}


/* --->>> Update <<<--- */
void SpaceLevel::update(float deltaTime)
{
	_updatePlayer(deltaTime);
	_updateAlien(deltaTime);
	_updateMeteors(deltaTime);
	_updateCrystals(deltaTime);
	_updateBullet(deltaTime);

	_updateLightShaders();
	_updateGuiTexts();

	_updateOutcomes();
}

void SpaceLevel::_updatePlayer(float deltaTime)
{
	_player->update(deltaTime);
	_player->getStats()->reloadBullet(deltaTime);

	// >>> Collisions <<<
	_collidePlayer();
}

void SpaceLevel::_updateAlien(float deltaTime)
{
	// Aliens
	for (auto alien = _aliens.begin(); alien != _aliens.end();)
	{
		// Update
		(*alien)->setPlayerPos(_player->getCameraPosition());
		(*alien)->update(deltaTime);

		// >>> Collisions <<<
		_collideAlien(alien);
	}
}

void SpaceLevel::_updateMeteors(float deltaTime)
{
	// Meteors
	for (auto meteor = _meteors.begin(); meteor != _meteors.end();)
	{
		// Update
		(*meteor)->update(deltaTime);

		// >>> Collisions <<<
		_collideMeteor(meteor);
	}
}

void SpaceLevel::_updateCrystals(float deltaTime)
{
	// Crystals
	for (auto crystal = _crystals.begin(); crystal != _crystals.end();)
	{
		// Update
		(*crystal)->update(deltaTime);

		// >>> Collisions <<<
		_collideCrystal(crystal);
	}
}

void SpaceLevel::_updateBullet(float deltaTime)
{
	// Bullet
	if (_bullet)
	{
		if (_bullet->isDead())
		{
			// Kill
			delete _bullet;
			_bullet = nullptr;
		}
		else
		{
			// Update
			_bullet->update(deltaTime);
		}
	}
}

void SpaceLevel::_updateLightShaders()
{
	_shaderProgram->useShader();
	_setLightUniforms(*_shaderProgram);
}

void SpaceLevel::_updateGuiTexts()
{
#ifndef DIST
	PlayerStats* stats = _player->getStats();

	// Health info
	std::stringstream streamForHealth;
	streamForHealth << std::fixed << std::setprecision(4);
	streamForHealth << stats->getHitPoints() << "/" << stats->getMaxHitPoints();
	_healthValueText.setText(streamForHealth.str());

	// Points info
	std::stringstream streamForCrystals;
	streamForCrystals << std::fixed << std::setprecision(4);
	streamForCrystals << stats->getPoints() << "/" << crystalsInstances;
	_crystalsValueText.setText(streamForCrystals.str());

	// Shooting info
	if (stats->canIShoot())
	{
		_bulletLabel.setText("Bullet:");
		_bulletValueText.setText("loaded!");
	}
	else
	{
		std::stringstream streamForBullet;
		streamForBullet << std::fixed << std::setprecision(2);
		streamForBullet << stats->getReloadTime() << "/" << stats->getReloadMaxTime();
		_bulletLabel.setText("Loading:");
		_bulletValueText.setText(streamForBullet.str());
	}
#endif
}

void SpaceLevel::_updateOutcomes()
{
	// Outcomes
	if (crystalsInstances == _player->getStats()->getPoints())
	{
		_gameState->winLevel();
	}

	if (_player->getStats()->getHitPoints() == 0)
	{
		_gameState->looseLevel();
	}
}


/* --->>> Collisions <<<--- */
void SpaceLevel::_collidePlayer()
{
	// Player <-> World border
	glm::vec3 playerPos = _player->getCameraPosition();
	glm::vec3 sphereCenter = glm::vec3(0, 0, 0);

	float distanceFromCenter = glm::distance(playerPos, sphereCenter);

	if (distanceFromCenter > worldRadius) {
		glm::vec3 newPosition = sphereCenter + ((playerPos - sphereCenter) / distanceFromCenter) * worldRadius;
		_player->setCameraPosition(newPosition);
	}
}

void SpaceLevel::_collideAlien(std::vector<Alien*>::iterator& alien)
{
	// Alien <-> World border
	if (glm::distance((*alien)->getPosition(), Mathf::zeroVec()) > worldRadius)
	{
		(*alien)->changeDirectionOnCollision();
	}

	++alien;
}

void SpaceLevel::_collideMeteor(std::vector<Meteor*>::iterator& meteor)
{
	// Meteor <-> World border
	if (glm::distance((*meteor)->getPosition(), Mathf::zeroVec()) > worldRadius)
	{
		(*meteor)->changeDirectionOnCollision();
	}

	// Meteor <-> Player
	PlayerStats* stats = _player->getStats();
	if (Mathf::areSpheresCollided(_player->getCameraPosition(), stats->getPlayerRadius(), (*meteor)->getPosition(), (*meteor)->getColliderRadius()))
	{
		stats->takeDamage(20);

		Debug::Log("Collision: Player <---> " + (*meteor)->getName());
		Debug::Log("Player health: " + std::to_string(stats->getHitPoints()));

		(*meteor)->destroy();
		meteor = _meteors.erase(meteor);
	}
	// Meteor <-> Bullet
	else if (_bullet && !_bullet->isDead() && Mathf::areSpheresCollided(_bullet->getPosition(), _bullet->getColliderRadius(), (*meteor)->getPosition(), (*meteor)->getColliderRadius()))
	{
		Debug::Log("Collision: Bullet <---> " + (*meteor)->getName());

		(*meteor)->destroy();
		_bullet->destroy();

		meteor = _meteors.erase(meteor);
		_bullet = nullptr;
	}
	else { ++meteor; }
}

void SpaceLevel::_collideCrystal(std::vector<Crystal*>::iterator& crystal)
{
	// Crystal <-> Player
	PlayerStats* stats = _player->getStats();
	if (Mathf::areSpheresCollided(_player->getCameraPosition(), stats->getPlayerRadius(), (*crystal)->getPosition(), (*crystal)->getColliderRadius()))
	{
		stats->addPoint();

		Debug::Log("Collision: Player <---> " + (*crystal)->getName());

		(*crystal)->destroy();
		crystal = _crystals.erase(crystal);
	}
	else { ++crystal; }
}


/* --->>> Lights <<<--- */
void SpaceLevel::_setLightUniforms(ShaderLightProgram& shaderProgram)
{
	int playerLights = 1;
	int bulletLights = 0;
	if (_bullet) { bulletLights = 1; }

	shaderProgram.setNumberOfLights(playerLights + _crystals.size() + bulletLights);
	char lightIndex[20];
	int currentLightsLimit = 0;

	// Default lights
	sprintf_s(lightIndex, 20, "pointLights[%d].", 0);
	std::string index { lightIndex };
	shaderProgram.setLightUniforms(*(_player->getLight()), index);
	currentLightsLimit = 1;


	// Crystals lights
	for (int i = currentLightsLimit; i < _crystals.size() + currentLightsLimit; i++)
	{
		sprintf_s(lightIndex, 20, "pointLights[%d].", i);
		std::string index { lightIndex };

		int objIndex = i - currentLightsLimit;
		shaderProgram.setLightUniforms(*(_crystals[objIndex]->getLight()), index);
	}
	currentLightsLimit += _crystals.size();


	// Bullet lights
	if (_bullet && !_bullet->isDead())
	{
		sprintf_s(lightIndex, 20, "pointLights[%d].", currentLightsLimit);
		std::string index{ lightIndex };
		shaderProgram.setLightUniforms(*(_bullet->getLight()), index);
	}
}


/* --->>> Render <<<--- */
void SpaceLevel::draw(float deltaTime, bool wireframe)
{
	_shaderProgram->useShader();
	_player->setCameraUniforms(_shaderProgram);

	for (int i = 0; i < _aliens.size(); i++)
	{
		_aliens[i]->draw(_shaderProgram);
	}

	for (int i = 0; i < _meteors.size(); i++)
	{
		_meteors[i]->draw(_shaderProgram);
	}

	for (int i = 0; i < _crystals.size(); i++)
	{
		_crystals[i]->draw(_shaderProgram);
	}

	if (_bullet && !_bullet->isDead())
	{
		_bullet->draw(_shaderProgram);
	}

	_skybox->draw(_player->getCameraPosition(), _player->getDirection(), _player->getUp());
	_drawGui();
}


/* --->>> GUI <<<--- */
void SpaceLevel::_drawGui()
{
	if (_hudActivated)
	{
		_HUD.draw();
	}

#ifndef DIST
	_textShader->useShader();
	auto projection = glm::ortho(0.0f, static_cast<float>(Config::g_defaultWidth), 0.0f, static_cast<float>(Config::g_defaultHeight));
	_textShader->setMat4("MVP", projection);

	_healthLabel.render(*_textShader);
	_healthValueText.render(*_textShader);

	_crystalsLabel.render(*_textShader);
	_crystalsValueText.render(*_textShader);

	_bulletLabel.render(*_textShader);
	_bulletValueText.render(*_textShader);
#endif

	if (_hudChangeLatch > 0)
		_hudChangeLatch--;
}

void SpaceLevel::_toggleHUD()
{
	if (!(_hudChangeLatch > 0))
	{
		_hudActivated = !_hudActivated;
		_hudChangeLatch = 10;
	}
}


/* --->>> Shooting <<<--- */
void SpaceLevel::_shootBullet()
{
	PlayerStats* stats = _player->getStats();
	if (stats->canIShoot())
	{
		// Bullet spawn
		_bullet = _spawnBullet();
		stats->shoot();
	}
	else
	{
		Debug::LogWarning("Can't shoot bullet");
	}
}

Bullet* SpaceLevel::_spawnBullet()
{
	GameObject* model = new GameObject(new Material(*_bulletMaterialPrefab), new Mesh(*_bulletMeshPrefab));
	Bullet* bullet = new Bullet(model, "Bullet", 7, _player);
	return bullet;
}