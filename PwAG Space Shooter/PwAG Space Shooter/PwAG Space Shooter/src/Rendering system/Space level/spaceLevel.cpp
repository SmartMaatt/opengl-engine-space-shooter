#include "pch.h"
#include "spaceLevel.h"
#include <set>
#include <ctime>

#include "../Rendering system/Model/objReader.h"
#include "../Rendering system/Model/vboIndexer.h"
#include "../SourceDep/stb_image.h"

/* --->>> Constructors / Destructor <<<--- */
SpaceLevel::SpaceLevel(GameState* gameState, int levelNumber) :
	_tmpDefaultFont(std::move(Font("res/Fonts/Segan.ttf", 32))), _levelLabel(270, 50, "Level:", _tmpDefaultFont),
	_healthLabel(20, 50, "Health:", _tmpDefaultFont), _healthValueText(140, 53, "0", _tmpDefaultFont),
	_aliensLabel(20, 90, "Aliens:", _tmpDefaultFont), _aliensValueText(140, 93, "0", _tmpDefaultFont),
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
	playerShootTimeout = levelInfo.playerShootTimeot;
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
	delete _medkitMaterialPrefab;
	delete _playerBulletMaterialPrefab;
	delete _alienBulletMaterialPrefab;

	delete _alienMeshPrefab;
	delete _meteorMeshPrefab;
	delete _medkitMeshPrefab;
	delete _bulletMeshPrefab;

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

	for (size_t i = 0; i < _medkits.size(); i++)
	{
		_medkits[i]->destroy();
	}

	for (size_t i = 0; i < _bullets.size(); i++)
	{
		_bullets[i]->destroy();
	}
}


/* --->>> Input <<<--- */
void SpaceLevel::input(float deltaTime, GameReference gameReference, Keyboard& keyboard, Mouse& mouse)
{
	_player->input(gameReference, keyboard, deltaTime);

	// Shooting
	if (keyboard.keyState[static_cast<int>(Keyboard::Key::eKeyF)])
	{
		_shootPlayerBullet();
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

	Texture* meteorTexture = new Texture(Texture::createTextureFromFile("res/Textures/Asteroid/asteroid.png", Texture::Type::PNG));
	Texture* meteorSpecular = new Texture(Texture::createTextureFromFile("res/Textures/Asteroid/asteroid_specular.png", Texture::Type::SPECULAR));
	Texture* medkitTexture = new Texture(Texture::createTextureFromFile("res/Textures/Beer/Beer_Bottle_TEX.png", Texture::Type::PNG));
	Texture* medkitSpecular = new Texture(Texture::createTextureFromFile("res/Textures/Beer/Beer_Bottle_roughness.png", Texture::Type::SPECULAR));

	Texture* playerBulletTexture = new Texture(Texture::createTextureFromFile("res/Textures/Bullet/blue_sphere.png", Texture::Type::PNG));
	Texture* alienBulletTexture = new Texture(Texture::createTextureFromFile("res/Textures/Bullet/green_sphere.png", Texture::Type::PNG));

	// To remove allocation at the end of scene
	_textures.push_back(alienTexture);
	_textures.push_back(alienSpecular);
	_textures.push_back(alienNormal);
	_textures.push_back(meteorTexture);
	_textures.push_back(meteorSpecular);
	_textures.push_back(medkitTexture);
	_textures.push_back(medkitSpecular);
	_textures.push_back(playerBulletTexture);
	_textures.push_back(alienBulletTexture);

	_alienMaterialPrefab = new Material(alienTexture, alienSpecular, alienNormal, 0, 1, glm::vec3(0.1));
	_meteorMaterialPrefab = new Material(meteorTexture, meteorSpecular, nullptr, 0, 1, glm::vec3(0.1));
	_medkitMaterialPrefab = new Material(medkitTexture, medkitSpecular, nullptr, 0, 1, glm::vec3(0.1));
	_playerBulletMaterialPrefab = new Material(playerBulletTexture, nullptr, nullptr, 0, 1, glm::vec3(0.25));
	_alienBulletMaterialPrefab = new Material(alienBulletTexture, nullptr, nullptr, 0, 1, glm::vec3(0.25));
}

void SpaceLevel::_initObjModels()
{
	// Loading data from obj
	DataOBJ alienMeshData = readObj("res/Models/alien.obj");
	DataOBJ meteorMeshData = readObj("res/Models/asteroid.obj");
	DataOBJ medkitMeshData = readObj("res/Models/beer.obj");
	DataOBJ bulletMeshData = readObj("res/Models/sphere.obj");

	// Instantiating meshes prefabs
	_alienMeshPrefab = new Mesh(alienMeshData, Mathf::zeroVec());
	_meteorMeshPrefab = new Mesh(meteorMeshData, Mathf::zeroVec());
	_medkitMeshPrefab = new Mesh(medkitMeshData, Mathf::zeroVec());
	_bulletMeshPrefab = new Mesh(bulletMeshData, Mathf::zeroVec());

	// Player
	_player = new Player(startPosition, playerShootTimeout);

	// Aliens
	for (int i = 0; i < enemiesInstances; i++)
	{
		GameObject* model = new GameObject(new Material(*_alienMaterialPrefab), new Mesh(*_alienMeshPrefab));
		Alien* alien = new Alien(model, "Alien " + std::to_string(i), worldRadius, Mathf::randVal(enemiesBulletShootInterval.first, enemiesBulletShootInterval.second));
		_aliens.push_back(alien);
	}

	// Meteors
	for (int i = 0; i < meteorsInstances; i++)
	{
		GameObject* model = new GameObject(new Material(*_meteorMaterialPrefab), new Mesh(*_meteorMeshPrefab));
		Meteor* entity = new Meteor(model, "Meteor " + std::to_string(i), worldRadius);
		_meteors.push_back(entity);
	}

	// Medkits
	for (int i = 0; i < medkitsInstances; i++)
	{
		GameObject* model = new GameObject(new Material(*_medkitMaterialPrefab), new Mesh(*_medkitMeshPrefab));
		Medkit* crystal = new Medkit(model, "Medkit " + std::to_string(i), worldRadius);
		_medkits.push_back(crystal);
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
	_levelLabel.setColor(glm::vec3(1, 1, 1));
	std::stringstream levelStream;
	levelStream << std::fixed << std::setprecision(4);
	levelStream << "Level: " << levelID + 1;
	_levelLabel.setText(levelStream.str());

	_bulletLabel.setColor(glm::vec3(0, 0, 1));
	_bulletValueText.setColor(glm::vec3(0, 0, 1));

	_aliensLabel.setColor(glm::vec3(0, 1, 0));
	_aliensValueText.setColor(glm::vec3(0, 1, 0));

	_healthLabel.setColor(glm::vec3(1, 0, 0));
	_healthValueText.setColor(glm::vec3(1, 0, 0));
}


/* --->>> Update <<<--- */
void SpaceLevel::update(float deltaTime)
{
	_updatePlayer(deltaTime);
	_updateAliens(deltaTime);
	_updateMeteors(deltaTime);
	_updateMedkits(deltaTime);
	_updateBullets(deltaTime);

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

void SpaceLevel::_updateAliens(float deltaTime)
{
	// Aliens
	for (auto alien = _aliens.begin(); alien != _aliens.end();)
	{
		// Update
		(*alien)->setPlayerPos(_player->getCameraPosition());
		(*alien)->update(deltaTime);

		// >>> Shooting <<<
		if ((*alien)->isReadyToShoot())
		{
			_bullets.push_back(_spawnAlienBullet(*alien));
			(*alien)->Shoot();
		}

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

void SpaceLevel::_updateMedkits(float deltaTime)
{
	// Crystals
	for (auto medkit = _medkits.begin(); medkit != _medkits.end();)
	{
		// Update
		(*medkit)->update(deltaTime);

		// >>> Collisions <<<
		_collideMedkit(medkit);
	}
}

void SpaceLevel::_updateBullets(float deltaTime)
{
	// Bullets
	for (auto bullet = _bullets.begin(); bullet != _bullets.end();)
	{
		if ((*bullet)->isDead())
		{
			// Kill
			(*bullet)->destroy();
			bullet = _bullets.erase(bullet);
		}
		else
		{
			// Update
			(*bullet)->update(deltaTime);
			++bullet;
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
	std::stringstream streamForAliens;
	streamForAliens << std::fixed << std::setprecision(4);
	streamForAliens << (enemiesInstances - _aliens.size()) << "/" << enemiesInstances;
	_aliensValueText.setText(streamForAliens.str());

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
	if (_aliens.size() == 0)
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

	// Player <-> Bullet
	for (auto bullet = _bullets.begin(); bullet != _bullets.end();)
	{
		if ((*bullet)->getAge() > 0.5f && Mathf::areSpheresCollided((*bullet)->getPosition(), (*bullet)->getColliderRadius(), _player->getCameraPosition(), _player->getStats()->getPlayerRadius()))
		{
			Debug::Log("Collision: Bullet <---> Player");

			_player->getStats()->takeDamage(15);

			(*bullet)->destroy();
			bullet = _bullets.erase(bullet);
			return;
		}
		else
		{
			++bullet;
		}
	}
}

void SpaceLevel::_collideAlien(std::vector<Alien*>::iterator& alien)
{
	// Alien <-> World border
	if (glm::distance((*alien)->getPosition(), Mathf::zeroVec()) > worldRadius)
	{
		(*alien)->changeDirectionOnCollision();
	}

	// Alien <-> Player
	PlayerStats* stats = _player->getStats();
	if (Mathf::areSpheresCollided(_player->getCameraPosition(), stats->getPlayerRadius(), (*alien)->getPosition(), (*alien)->getColliderRadius()))
	{
		stats->takeDamage(50);

		Debug::Log("Collision: Player <---> " + (*alien)->getName());
		Debug::Log("Player health: " + std::to_string(stats->getHitPoints()));

		(*alien)->destroy();
		alien = _aliens.erase(alien);
		return;
	}
	// Alien <-> Bullet
	else
	{
		for (auto bullet = _bullets.begin(); bullet != _bullets.end();)
		{
			if ((*bullet)->getAge() > 0.5f && Mathf::areSpheresCollided((*bullet)->getPosition(), (*bullet)->getColliderRadius(), (*alien)->getPosition(), (*alien)->getColliderRadius()))
			{
				Debug::Log("Collision: Bullet <---> " + (*alien)->getName());

				(*alien)->destroy();
				(*bullet)->destroy();

				alien = _aliens.erase(alien);
				bullet = _bullets.erase(bullet);
				return;
			}
			else
			{
				++bullet;
			}
		}
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
		return;
	}
	// Meteor <-> Bullet
	else
	{
		for (auto bullet = _bullets.begin(); bullet != _bullets.end();)
		{
			if (Mathf::areSpheresCollided((*bullet)->getPosition(), (*bullet)->getColliderRadius(), (*meteor)->getPosition(), (*meteor)->getColliderRadius()))
			{
				Debug::Log("Collision: Bullet <---> " + (*meteor)->getName());

				(*bullet)->destroy();
				bullet = _bullets.erase(bullet);
				return;
			}
			else
			{
				++bullet;
			}
		}
	}
	++meteor;
}

void SpaceLevel::_collideMedkit(std::vector<Medkit*>::iterator& medkit)
{
	// Crystal <-> Player
	PlayerStats* stats = _player->getStats();
	if (Mathf::areSpheresCollided(_player->getCameraPosition(), stats->getPlayerRadius(), (*medkit)->getPosition(), (*medkit)->getColliderRadius()))
	{
		stats->heal(50);

		Debug::Log("Collision: Player <---> " + (*medkit)->getName());

		(*medkit)->destroy();
		medkit = _medkits.erase(medkit);
	}
	else { ++medkit; }
}


/* --->>> Lights <<<--- */
void SpaceLevel::_setLightUniforms(ShaderLightProgram& shaderProgram)
{
	int playerLights = 1;

	shaderProgram.setNumberOfLights(playerLights + _medkits.size() + _bullets.size());
	char lightIndex[20];
	int currentLightsLimit = 0;

	// Default lights
	sprintf_s(lightIndex, 20, "pointLights[%d].", 0);
	std::string index { lightIndex };
	shaderProgram.setLightUniforms(*(_player->getLight()), index);
	currentLightsLimit += playerLights;


	// Crystals lights
	for (int i = currentLightsLimit; i < _medkits.size() + currentLightsLimit; i++)
	{
		sprintf_s(lightIndex, 20, "pointLights[%d].", i);
		std::string index { lightIndex };

		int objIndex = i - currentLightsLimit;
		shaderProgram.setLightUniforms(*(_medkits[objIndex]->getLight()), index);
	}
	currentLightsLimit += _medkits.size();


	// Bullets lights
	for (int i = currentLightsLimit; i < _bullets.size() + currentLightsLimit; i++)
	{
		sprintf_s(lightIndex, 20, "pointLights[%d].", i);
		std::string index{ lightIndex };

		int objIndex = i - currentLightsLimit;
		shaderProgram.setLightUniforms(*(_bullets[objIndex]->getLight()), index);
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

	for (int i = 0; i < _medkits.size(); i++)
	{
		_medkits[i]->draw(_shaderProgram);
	}

	for (int i = 0; i < _bullets.size(); i++)
	{
		_bullets[i]->draw(_shaderProgram);
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

	_levelLabel.render(*_textShader);

	_bulletLabel.render(*_textShader);
	_bulletValueText.render(*_textShader);

	_aliensLabel.render(*_textShader);
	_aliensValueText.render(*_textShader);

	_healthLabel.render(*_textShader);
	_healthValueText.render(*_textShader);
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
void SpaceLevel::_shootPlayerBullet()
{
	PlayerStats* stats = _player->getStats();
	if (stats->canIShoot())
	{
		// Bullet spawn
		_bullets.push_back(_spawnPlayerBullet());
		stats->shoot();
	}
}

Bullet* SpaceLevel::_spawnPlayerBullet()
{
	GameObject* model = new GameObject(new Material(*_playerBulletMaterialPrefab), new Mesh(*_bulletMeshPrefab));
	Bullet* bullet = new Bullet(model, "Bullet", 7, _player->getCameraPosition(), _player->getDirection(), {0, 0, 1});
	return bullet;
}

Bullet* SpaceLevel::_spawnAlienBullet(Alien* alien)
{
	GameObject* model = new GameObject(new Material(*_alienBulletMaterialPrefab), new Mesh(*_bulletMeshPrefab));
	Bullet* bullet = new Bullet(model, "Bullet", 7, alien->getPosition(), alien->getDirection(), { 0, 1, 0 });
	return bullet;
}