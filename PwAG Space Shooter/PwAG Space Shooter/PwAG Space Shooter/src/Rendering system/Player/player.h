#pragma once
#include "../../State machine/gameAssets.h"
#include "../../Event system/keyboard.h"
#include "../../Event system/mouse.h"

class Player
{
public:
	Player();
	Player(glm::vec3 position = glm::vec3(0.0f));

	void setCameraUniforms(ShaderProgram* shaderProgram);
	void updateInput(GameReference gameReference, Keyboard& keyboard, Mouse& mouse, float deltaTime);
	
	void setCameraPosition(glm::vec3 position);

	glm::vec3 getCameraPosition() const;

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

	glm::vec3 getDirection();

	virtual ~Player();

private:
	// Initial position : on +Z
	glm::vec3 position = glm::vec3(0, 0, 5);
	// Initial horizontal angle : toward -Z
	float horizontalAngle = 3.14f;
	// Initial vertical angle : none
	float verticalAngle = 0.0f;
	// Initial Field of View
	float initialFoV = 45.0f;

	glm::vec3 direction = glm::vec3(0.0f);
	glm::vec3 right = glm::vec3(0.0f);
	glm::vec3 up = glm::vec3(0.0f);

	float speed = 3.0f; // 3 units / second
	float mouseSpeed = 0.005f;

	glm::mat4 ViewMatrix = glm::mat4(0.0f);
	glm::mat4 ProjectionMatrix = glm::mat4(0.0f);
};