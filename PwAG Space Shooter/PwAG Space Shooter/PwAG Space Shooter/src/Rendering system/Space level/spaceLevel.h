#pragma once
#include "../Rendering system/Model/gameObject.h"
#include "../Rendering system/Player/player.h"
#include "../Rendering system/Player/PlayerStats.h"
#include "../Rendering system/Lighting/point.h"
#include "../Rendering system/Entity/entity.h"
#include "../Rendering system/Entity/alien.h"
#include "../Rendering system/Entity/meteor.h"
#include "../Rendering system/Entity/medkit.h"
#include "../Rendering system/Entity/bullet.h"
#include "../Rendering system/Model/indexedDataOBJ.h"
#include "../State machine/gameState.h"
#include "../Rendering system/Skybox/skybox.h"
#include "../Rendering system/Space level/spaceLevelFileReader.h"

class SpaceLevel
{
public:
	int levelID = 0;
	int enemiesInstances = 0;
	std::pair<float, float> enemiesBulletShootInterval = std::pair<float, float>();
	float playerShootTimeout = 0.0;
	int medkitsInstances = 0;
	int meteorsInstances = 20;
	float worldRadius = 12;
	glm::vec3 startPosition = glm::vec3(0, 0, 0);

	SpaceLevelFileReader levelFileReader;

	// Skybox cubemaps
	std::string facesCubemap[6] =
	{
		"res/Textures/Skybox/right.png",
		"res/Textures/Skybox/left.png",
		"res/Textures/Skybox/top.png",
		"res/Textures/Skybox/bottom.png",
		"res/Textures/Skybox/front.png",
		"res/Textures/Skybox/back.png"
	};

	// Constructors / Destructor
	SpaceLevel(GameState* gameState, int levelNumber);
	~SpaceLevel();

	// Input
	void input(float deltaTime, GameReference gameReference, Keyboard& keyboard, Mouse& mouse);

	// Update
	void update(float deltaTime);

	// Render
	void draw(float deltaTime, bool wireframe);

private:
	// Initialization
	void _initLevel();
	void _initMatrixMVP();
	void _initLevelShaders();
	void _initLevelMaterials();
	void _initObjModels();
	void _initText();

	// Update
	void _updatePlayer(float deltaTime);
	void _updateAliens(float deltaTime);
	void _updateMeteors(float deltaTime);
	void _updateMedkits(float deltaTime);
	void _updateBullets(float deltaTime);
	void _updateLightShaders();
	void _updateGuiTexts();
	void _updateOutcomes();

	// Collisions
	void _collidePlayer();
	void _collideAlien(std::vector<Alien*>::iterator& alien);
	void _collideMeteor(std::vector<Meteor*>::iterator& meteor);
	void _collideMedkit(std::vector<Medkit*>::iterator& medkit);

	// Lights
	void _setLightUniforms(ShaderLightProgram& shader);

	// GUI
	void _drawGui();
	void _toggleHUD();

	// Shooting
	void _shootPlayerBullet();
	Bullet* _spawnPlayerBullet();
	Bullet* _spawnAlienBullet(Alien* alien);

	// Instances
	GameState* _gameState;
	Skybox* _skybox;
	Player* _player;
	std::vector<Alien*> _aliens;
	std::vector<Meteor*> _meteors;
	std::vector<Medkit*> _medkits;
	std::vector<Bullet*> _bullets;

	// Shaders
	ShaderLightProgram* _shaderProgram;
	Shader _vertexShader;
	Shader _fragmentShader;

	// Textures
	std::vector<Texture*> _textures;

	// Materials
	Material* _alienMaterialPrefab;
	Material* _meteorMaterialPrefab;
	Material* _medkitMaterialPrefab;
	Material* _playerBulletMaterialPrefab;
	Material* _alienBulletMaterialPrefab;

	// Meshes
	Mesh* _alienMeshPrefab;
	Mesh* _meteorMeshPrefab;
	Mesh* _medkitMeshPrefab;
	Mesh* _bulletMeshPrefab;

	// GUI
	Font _tmpDefaultFont;
	ShaderProgram* _textShader;

	Text _levelLabel;
	Text _healthLabel;
	Text _healthValueText;
	Text _aliensLabel;
	Text _aliensValueText;
	Text _bulletLabel;
	Text _bulletValueText;

	Sprite _HUD;
	bool _hudActivated = true;
	int _hudChangeLatch = 0;
};