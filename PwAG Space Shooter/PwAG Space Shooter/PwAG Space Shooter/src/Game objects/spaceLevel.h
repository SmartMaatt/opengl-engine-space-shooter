#pragma once
#include "gameObject.h"
#include "../Rendering system/Player/player.h"
#include "../Rendering system/Player/PlayerStats.h"
#include "../Rendering system/Lighting/point.h"
#include "../Rendering system/Entity/entity.h"

class SpaceLevel
{
public:
	Player* player;
	PlayerStats* playerStats;

	glm::vec3 startPosition;
	glm::vec3 endPosition;

	// Initialization
	SpaceLevel();
	void initMaze();
	void initMatrixMVP();
	void initMazeShaders();
	void initMazeMaterials();
	void initMazeTextures();
	void initObjModels();

	float randVal(float LO, float HI);

	// Update
	void updateMaze(float deltaTime);
	void updateLightShaders();

	// Render
	void drawMaze(float deltaTime, bool wireframe);

	// Collision
	void playerToMeteoCollision();
	bool areSpheresCollided(glm::vec3 center1, float rad1, glm::vec3 center2, float rad2);
	
	// Deserialization
	virtual ~SpaceLevel();

private:
	void defaultRender(float deltaTime);
	void setLightUniforms(ShaderProgram& shader);
	std::vector<GLfloat> generateOffset(GLfloat x, GLfloat y, GLfloat z);

	std::vector<Light::Point> pointLights;
	std::vector<Entity*> meteos;

	ShaderProgram* shaderProgram;
	Shader vertexShader;
	Shader fragmentShader;

	Material* material;

	Texture* torchTexture;
	Texture* specularMapWood;
};