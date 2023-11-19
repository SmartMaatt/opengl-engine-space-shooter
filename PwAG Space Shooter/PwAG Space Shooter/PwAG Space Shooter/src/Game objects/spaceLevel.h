#pragma once
#include "gameObject.h"
#include "../Rendering system/Player/player.h"
#include "../Rendering system/Player/PlayerStats.h"
#include "../Rendering system/Lighting/point.h"
#include "../Rendering system/Entity/entity.h"
#include "../Rendering system/Entity/meteor.h"
#include "../Rendering system/Entity/crystal.h"
#include "../Rendering system/Entity/bullet.h"
#include "../Rendering system/Model/indexedDataOBJ.h"
#include "../State machine/gameState.h"

class SpaceLevel
{
public:
	int meteorsInstances = 40;
	int crystalsInstances = 5;
	float worldRadius = 10;
	glm::vec3 startPosition = glm::vec3(0, 0.5f, 0);

	// Constructors / Destructor
	SpaceLevel(GameState* gameState);
	~SpaceLevel();

	// Getters / Setters
	Player* getPlayer();

	// Input
	void input(float deltaTime, GameReference gameReference, Keyboard& keyboard, Mouse& mouse);

	// Update
	void update(float deltaTime);

	// Render
	void draw(float deltaTime, bool wireframe);

private:
	// Initialization
	void initLevel();
	void initMatrixMVP();
	void initLevelShaders();
	void initLevelMaterials();
	void initObjModels();
	void initText();

	// Update
	void updatePlayer(float deltaTime);
	void updateMeteors(float deltaTime);
	void updateCrystals(float deltaTime);
	void updateBullet(float deltaTime);
	void updateLightShaders();
	void updateGuiTexts();
	void updateOutcomes();

	// Collisions
	void collideMeteor(std::vector<Meteor*>::iterator& meteor);
	void collideCrystal(std::vector<Crystal*>::iterator& crystal);

	// Lights
	void setLightUniforms(ShaderProgram& shader);

	// GUI
	void drawGui();
	void ToggleHUD();

	// Shooting
	void shootBullet();
	Bullet* spawnBullet();

	// Instances
	GameState* gameState;
	Player* player;
	std::vector<Meteor*> meteors;
	std::vector<Crystal*> crystals;
	Bullet* bullet;

	// Shaders
	ShaderProgram* shaderProgram;
	Shader vertexShader;
	Shader fragmentShader;

	// Textures
	std::vector<Texture*> textures;

	// Materials
	Material* meteorMaterialPrefab;
	Material* crystalMaterialPrefab;
	Material* bulletMaterialPrefab;

	// Meshes
	Mesh* meteorMeshPrefab;
	Mesh* crystalMeshPrefab;
	Mesh* bulletMeshPrefab;

	// GUI
	Font tmpDefaultFont;
	ShaderProgram textShader;

	Text healthLabel;
	Text healthValueText;
	Text crystalsLabel;
	Text crystalsValueText;
	Text bulletLabel;
	Text bulletValueText;

	Sprite HUD;
	bool hudActivated = true;
	int hudChangeLatch = 0;
};