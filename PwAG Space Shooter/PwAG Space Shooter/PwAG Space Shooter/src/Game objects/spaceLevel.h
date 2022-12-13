#pragma once
#include "gameObject.h"
#include "../Rendering system/Player/player.h"
#include "../Rendering system/Lighting/point.h"
#include "../Rendering system/Entity/entity.h"

class SpaceLevel
{
public:
	Player* player;
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
	void setLightUniforms(ShaderProgram& shader);
	std::vector<GLfloat> generateOffset(GLfloat x, GLfloat y, GLfloat z);

	std::vector<Light::Point> pointLights;
	std::vector<Entity*> torches;

	GameObject* dupa1;
	GameObject* dupa2;
	GameObject* dupa3;

	ShaderProgram* shaderProgram;
	Shader vertexShader;
	Shader fragmentShader;

	Material* material;

	Texture* torchTexture;
	Texture* specularMapWood;
};