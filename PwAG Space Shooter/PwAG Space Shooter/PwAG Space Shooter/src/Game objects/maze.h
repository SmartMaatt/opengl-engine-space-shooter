#pragma once
#include "gameObject.h"
#include "smokeBomb.h"
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

class Maze
{
public:
	glm::vec3 startPosition;
	glm::vec3 endPosition;

	Maze();

	void initMaze();
	void initMatrixMVP();
	void initMazeShaders();
	void initMazeMaterials();
	void initMazeTextures();
	void initObjModels();

	Camera* camera;

	void drawMaze(float deltaTime, bool wireframe);
	void updateMaze(float deltaTime);
	void updateLightShaders();

	bool willBeCollisionWithWall(float deltaTime);
	bool willBeCollisionWithExit();

	void useSmokeBomb();

	virtual ~Maze();

private:
	void defaultRender(float deltaTime);
	
	void deferred_geometryPass(float deltaTime);
	void deferred_lightingPass(float deltaTime);

	void OIT_render(float deltaTime, bool wireframe);
	void OIT_solidPass(float deltaTime);
	void OIT_transparentPass(float deltaTime);
	void OIT_compositePass(float deltaTime);
	void OIT_finalPass(float deltaTime);

	void setLightUniforms(ShaderProgram& shader);
	void updateSmokeBombs(float deltaTime);

	void updateEnemy(float deltaTime);
	void updateRespawnPoint(float deltaTime);

	int mazeDimensionX = 30;
	int mazeDimensionY = 30;
	int** mazeIndexData;

	GameObject* walls;
	GameObject* floors;
	GameObject* ceilings;
	GameObject* torches;
	GameObject* exitDoors;
	GameObject* grass1;
	GameObject* grass2;
	GameObject* grass3;

	std::vector<RespawnPoint*> respawnPickup;
	std::vector<Enemy*> opponents;
	std::vector<Light::Point> pointLights;
	std::vector<ParticleEmitter> torchesParticleEmitters;

	std::vector<SmokeBomb> smokeBombs;
	const float smokeBombCooldown = 0.5f;
	float smokeBombCooldownLeft = 0.0f;

	ShaderProgram* shaderProgram;
	ShaderProgram* shaderGrassProgram;
	ShaderProgram* shaderPickupProgram;

	ShaderProgram shaderParticles;

	Shader vertexShader;
	Shader fragmentShader;

	Shader vertexShaderGrass;
	Shader fragmentShaderGrass;

	Shader vertexShaderPickup;
	Shader fragmentShaderPickup;

	Material* material;

	Texture* wallTexture;
	Texture* floorTexture;
	Texture* ceilingTexture;
	Texture* torchTexture;
	Texture* exitDoorTexture;
	Texture* grass_1Texture;
	Texture* grass_2Texture;
	Texture* grass_3Texture;
	Texture* spawnActiveTexture;
	Texture* spawnInactiveTexture;

	Texture* normalMapWall;
	Texture* normalMapCeiling;
	Texture* normalMapFloor;
	Texture* normalMapDoors;

	Texture* specularMapWall;
	Texture* specularMapCeiling;
	Texture* specularMapFloor;
	Texture* specularMapWood;
	Texture* specularDoors;

	Texture* enemyTexture;

	std::vector<GLfloat> offsetsWalls;
	std::vector<GLfloat> offsetsCeiling;
	std::vector<GLfloat> offsetsFloors;
	std::vector<GLfloat> offsetsTorches;
	std::vector<GLfloat> offsetsExitDoors;
	std::vector<GLfloat> offsetsGrass1;
	std::vector<GLfloat> offsetsGrass2;
	std::vector<GLfloat> offsetsGrass3;

	DeferredRenderer deferred;
	ShaderProgram shaderGeometryPass;
	ShaderProgram shaderLightingPass;

	OIT oit;
	VAO quadVAO;
	VBO quadVBO;

	ShaderProgram shaderOITpickup;
	ShaderProgram shaderOITparticle;
	ShaderProgram shaderOITcomposite;
	ShaderProgram shaderOITscreen;

	// A star algorithm
	struct cell {
		int parent_i, parent_j;
		double f, g, h;
	};

	PairFloat tracePath(cell cellDetails[][30], Pair dest);
	PairFloat aStarSearchPath(Pair src, Pair dest);
	Pair positionToXYPath(PairFloat position);
	bool isUnBlockedPath(int row, int col);
	bool isDestinationPath(int row, int col, Pair dest);
	double calculateHValuePath(int row, int col, Pair dest);
	bool isValidPath(int row, int col);
};

