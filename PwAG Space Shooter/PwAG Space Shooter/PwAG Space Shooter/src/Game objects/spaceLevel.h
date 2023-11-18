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

class SpaceLevel
{
public:
	int meteorsInstances = 40;
	int crystalsInstances = 5;
	float worldRadius = 10;

	Player* player;
	PlayerStats* playerStats;

	glm::vec3 startPosition;
	glm::vec3 endPosition;

	// Initialization
	SpaceLevel();
	void initLevel();
	void initMatrixMVP();
	void initLevelShaders();
	void initLevelMaterials();
	void initObjModels();
	void initText();

	// Update
	void updateLevel(float deltaTime);

	void updatePlayer(float deltaTime);
	void updateMeteors(float deltaTime);
	void collideMeteor(std::vector<Meteor*>::iterator& meteor);
	void updateCrystals(float deltaTime);
	void collideCrystal(std::vector<Crystal*>::iterator& crystal);
	void updateBullet(float deltaTime);
	void updateLightShaders();
	void updateTextValues();

	// Render
	void drawLevel(float deltaTime, bool wireframe);
	void drawGui();
	void ToggleHUD();

	// Shooting
	void shootBullet();

	// Deserialization
	virtual ~SpaceLevel();

private:
	void setLightUniforms(ShaderProgram& shader);
	Bullet* spawnBullet();

	// Instances
	std::vector<Light::Point> pointLights;
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

	// Text related
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