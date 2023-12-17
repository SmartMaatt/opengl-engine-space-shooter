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
	Player(glm::vec3 startPosition = glm::vec3(0.0f), float reloadTime = 0.5f);
	~Player();

	// Input
	void input(GameReference& gameReference, Keyboard& keyboard, float deltaTime);

	// Update
	void update(float deltaTime);

	// Getters / Setters
	void setCameraUniforms(ShaderProgram* shaderProgram);
	void setCameraPosition(glm::vec3 _position);

	glm::vec3 getCameraPosition();
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	glm::vec3 getDirection();
	glm::vec3 getUp();
	PlayerStats* getStats();
	Light::Point* getLight();

private:
	// Input
	void _processInput(GameReference& gameReference, Keyboard& keyboard, float deltaTime);
	void _updateMatricesFromInput();

	// Update
	void _updateLight();

	PlayerStats* _stats;
	Light::Point* _light;

	glm::vec3 _movementDirection = glm::vec3(0);
	glm::vec3 _position = glm::vec3(0, 0, 5);		// Initial position : on +Z
	float _horizontalAngle = 3.14f;					// Initial horizontal angle : toward -Z
	float _verticalAngle = 0.0f;					// Initial vertical angle : none
	float _initialFoV = 45.0f;						// Initial Field of View

	float _speed = 3.0f;							// 3 units / second
	float _mouseSpeed = 0.005f;

	glm::vec3 _direction = glm::vec3(0.0f);
	glm::vec3 _right = glm::vec3(0.0f);
	glm::vec3 _up = glm::vec3(0.0f);

	glm::mat4 _viewMatrix = glm::mat4(0.0f);
	glm::mat4 _projectionMatrix = glm::mat4(0.0f);
};