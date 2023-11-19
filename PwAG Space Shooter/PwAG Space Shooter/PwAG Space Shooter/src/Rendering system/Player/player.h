#pragma once
#include "playerStats.h"
#include "../../State machine/gameAssets.h"
#include "../../Event system/keyboard.h"
#include "../../Event system/mouse.h"

class Player
{
public:
	// Constructors / Destructor 
	Player();
	Player(glm::vec3 startPosition = glm::vec3(0.0f));
	~Player();

	// Input
	void input(GameReference& gameReference, Keyboard& keyboard, float deltaTime);

	// Update
	void update(float deltaTime);

	// Getters / Setters
	void setCameraUniforms(ShaderProgram* shaderProgram);
	void setCameraPosition(glm::vec3 position);
	
	glm::vec3 getCameraPosition();
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	glm::vec3 getDirection();
	PlayerStats* getStats();
	Light::Point* getLight();

private:
	// Input
	void processInput(GameReference& gameReference, Keyboard& keyboard, float deltaTime);
	void updateMatricesFromInput();

	// Update
	void updateLight();

	PlayerStats* stats;
	Light::Point* light;

	glm::vec3 position = glm::vec3(0, 0, 5);	// Initial position : on +Z
	float horizontalAngle = 3.14f;				// Initial horizontal angle : toward -Z
	float verticalAngle = 0.0f;					// Initial vertical angle : none
	float initialFoV = 45.0f;					// Initial Field of View

	float speed = 3.0f;							// 3 units / second
	float mouseSpeed = 0.005f;

	glm::vec3 direction = glm::vec3(0.0f);
	glm::vec3 right = glm::vec3(0.0f);
	glm::vec3 up = glm::vec3(0.0f);

	glm::mat4 viewMatrix = glm::mat4(0.0f);
	glm::mat4 projectionMatrix = glm::mat4(0.0f);
};