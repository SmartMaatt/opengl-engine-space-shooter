#pragma once
#include "gameObject.h"
#include "../Rendering system/Player/player.h"
#include "../Rendering system/Player/PlayerStats.h"
#include "../Rendering system/Lighting/point.h"
#include "../Rendering system/Entity/entity.h"
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
	void initLevelTextures();
	void initObjModels();
	void initText();

	// Randomization
	float randVal(float LO, float HI);
	glm::vec3 randCoordsInSphere(float radius);

	// Update
	void updateLevel(float deltaTime);

	void updatePlayer(float deltaTime);
	void updateMeteors(float deltaTime);
	void updateCrystals(float deltaTime);
	void updateBullet(float deltaTime);
	void updateLightShaders();
	void updateTextValues();

	// Render
	void drawLevel(float deltaTime, bool wireframe);
	void drawGui();
	void ToggleHUD();

	// Collision
	bool areSpheresCollided(glm::vec3 center1, float rad1, glm::vec3 center2, float rad2);
	
	// Shooting
	void shootBullet();

	// Deserialization
	virtual ~SpaceLevel();

private:
	void setLightUniforms(ShaderProgram& shader);
	Bullet* spawnBullet();

	std::vector<Light::Point> pointLights;
	std::vector<Entity*> meteors;
	std::vector<Crystal*> crystals;

	Bullet* bullet = nullptr;
	IndexedDataOBJ indexedBulletObjects;

	glm::vec3 zero = glm::vec3(0, 0, 0);
	glm::vec3 one = glm::vec3(1, 1, 1);

	ShaderProgram* shaderProgram;
	Shader vertexShader;
	Shader fragmentShader;

	Material* material;

	Texture* meteorTexture;
	Texture* specularMapMeteor;
	Texture* crystalTexture;
	Texture* specularMapCrystal;
	Texture* bulletTexture;

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