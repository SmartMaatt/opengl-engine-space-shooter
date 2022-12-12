#pragma once
#include "gameObject.h"
#include "../Rendering system/Player/player.h"
#include "../Rendering system/Lighting/point.h"
#include "../Rendering system/Particle system/particleEmitter.h"
#include "../../enemy.h"
#include "../../respawnPoint.h"
#include "../Rendering system/Deferred rendering/deferredRenderer.h"
#include "../Rendering system/OIT/oit.h"

typedef std::pair<double, std::pair<int, int>> pPair;
typedef std::pair<int, int> Pair;
typedef std::pair<float, float> PairFloat;

class SpaceLevel
{
public:
	Camera* player;
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

	// Update
	void updateMaze(float deltaTime);
	void updateLightShaders();

	// Render
	void drawMaze(float deltaTime, bool wireframe);

	// Collision
	bool willBeCollisionWithExit();
	
	// Deserialization
	virtual ~SpaceLevel();

private:
	void defaultRender(float deltaTime);
	void setLightUniforms(ShaderProgram& shader);;

	GameObject* torches;
	std::vector<Light::Point> pointLights;

	ShaderProgram* shaderProgram;
	Shader vertexShader;
	Shader fragmentShader;

	Material* material;

	Texture* torchTexture;
	Texture* specularMapWood;

	std::vector<GLfloat> offsetsTorches;
};