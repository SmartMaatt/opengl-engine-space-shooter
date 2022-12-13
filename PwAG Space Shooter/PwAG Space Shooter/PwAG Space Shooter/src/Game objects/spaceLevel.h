#pragma once
#include "gameObject.h"
#include "../Rendering system/Player/player.h"
#include "../Rendering system/Player/PlayerStats.h"
#include "../Rendering system/Lighting/point.h"
#include "../Rendering system/Entity/entity.h"
#include "../Rendering system/Entity/crystal.h"

class SpaceLevel
{
public:
	int meteorsInstances = 25;
	int crystalsInstances = 2;
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

	// Randomization
	float randVal(float LO, float HI);
	glm::vec3 randCoordsInSphere(float radius);

	// Update
	void updateLevel(float deltaTime);
	void updateLightShaders();

	// Render
	void drawLevel(float deltaTime, bool wireframe);

	// Collision

	bool areSpheresCollided(glm::vec3 center1, float rad1, glm::vec3 center2, float rad2);
	
	// Deserialization
	virtual ~SpaceLevel();

private:
	void setLightUniforms(ShaderProgram& shader);
	std::vector<GLfloat> generateOffset(GLfloat x, GLfloat y, GLfloat z);

	std::vector<Light::Point> pointLights;
	std::vector<Entity*> meteors;
	std::vector<Crystal*> crystals;

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
};