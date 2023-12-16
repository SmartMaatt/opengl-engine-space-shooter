#pragma once
#include "../Rendering system/Model/gameObject.h"
#include "../Rendering system/Player/player.h"
#include "../Rendering system/Player/PlayerStats.h"
#include "../Rendering system/Lighting/point.h"
#include "../Rendering system/Entity/entity.h"
#include "../Rendering system/Entity/meteor.h"
#include "../Rendering system/Entity/crystal.h"
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
	float playerShootTimeot = 0.0;
	int medkitsInstances = 0;
	int meteorsInstances = 40;
	int crystalsInstances = 5;
	float worldRadius = 10;
	glm::vec3 startPosition = glm::vec3(0, 0.5f, 0);

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
	void _updateMeteors(float deltaTime);
	void _updateCrystals(float deltaTime);
	void _updateBullet(float deltaTime);
	void _updateLightShaders();
	void _updateGuiTexts();
	void _updateOutcomes();

	// Collisions
	void _collidePlayer();
	void _collideMeteor(std::vector<Meteor*>::iterator& meteor);
	void _collideCrystal(std::vector<Crystal*>::iterator& crystal);

	// Lights
	void _setLightUniforms(ShaderLightProgram& shader);

	// GUI
	void _drawGui();
	void _toggleHUD();

	// Shooting
	void _shootBullet();
	Bullet* _spawnBullet();

	// Instances
	GameState* _gameState;
	Skybox* _skybox;
	Player* _player;
	std::vector<Meteor*> _meteors;
	std::vector<Crystal*> _crystals;
	Bullet* _bullet;

	// Shaders
	ShaderLightProgram* _shaderProgram;
	Shader _vertexShader;
	Shader _fragmentShader;

	// Textures
	std::vector<Texture*> _textures;

	// Materials
	Material* _meteorMaterialPrefab;
	Material* _crystalMaterialPrefab;
	Material* _bulletMaterialPrefab;

	// Meshes
	Mesh* _meteorMeshPrefab;
	Mesh* _crystalMeshPrefab;
	Mesh* _bulletMeshPrefab;

	// GUI
	Font _tmpDefaultFont;
	ShaderProgram* _textShader;

	Text _healthLabel;
	Text _healthValueText;
	Text _crystalsLabel;
	Text _crystalsValueText;
	Text _bulletLabel;
	Text _bulletValueText;

	Sprite _HUD;
	bool _hudActivated = true;
	int _hudChangeLatch = 0;
};