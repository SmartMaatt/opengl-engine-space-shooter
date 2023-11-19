#include "pch.h"
#include "player.h"
#include "GLM/include/gtc/matrix_transform.hpp"

/* --->>> Constructors / Destructor <<<--- */
Player::Player() {}

Player::Player(glm::vec3 startPosition)
{
	this->stats = new PlayerStats();
	this->light = new Light::Point({ 1,0,1 }, { 1,1,1 });

	this->position = startPosition;
	this->horizontalAngle = 3.14f;
	this->verticalAngle = 0.0f;
	this->initialFoV = 45.0f;

	this->speed = 3.0f;
	this->mouseSpeed = 0.0005f;
}

Player::~Player() 
{
	delete this->stats;
	delete this->light;
}


/* --->>> Input <<<--- */
void Player::input(GameReference& gameReference, Keyboard& keyboard, float deltaTime)
{
	processInput(gameReference, keyboard, deltaTime);
	updateMatricesFromInput();
}

void Player::processInput(GameReference& gameReference, Keyboard& keyboard, float deltaTime)
{
	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(gameReference->window, &xpos, &ypos);

	// Reset mouse position for next frame
	glfwSetCursorPos(gameReference->window, Config::g_defaultWidth / 2, Config::g_defaultHeight / 2);

	// Compute new orientation
	horizontalAngle += mouseSpeed * float(Config::g_defaultWidth / 2 - xpos);
	verticalAngle += mouseSpeed * float(Config::g_defaultHeight / 2 - ypos);

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	this->direction = glm::vec3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// Right vector
	this->right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	// Up vector
	this->up = glm::cross(right, direction);

	if (keyboard.keyState[static_cast<int>(Keyboard::Key::eKeyW)]) {
		this->position += direction * deltaTime * speed;
	}

	if (keyboard.keyState[static_cast<int>(Keyboard::Key::eKeyS)]) {
		this->position -= direction * deltaTime * speed;
	}

	if (keyboard.keyState[static_cast<int>(Keyboard::Key::eKeyA)]) {
		this->position -= right * deltaTime * speed;
	}

	if (keyboard.keyState[static_cast<int>(Keyboard::Key::eKeyD)]) {
		this->position += right * deltaTime * speed;
	}

	if (keyboard.keyState[static_cast<int>(Keyboard::Key::eKeySpace)]) {
		this->position += up * deltaTime * speed;
	}

	if (keyboard.keyState[static_cast<int>(Keyboard::Key::eKeyLeftShift)]) {
		this->position -= up * deltaTime * speed;
	}
}

void Player::updateMatricesFromInput()
{
	float FoV = initialFoV;
	projectionMatrix = glm::perspective(
		glm::radians(FoV),
		(float)Config::g_defaultWidth / (float)Config::g_defaultHeight,
		0.1f,
		100.0f
	);

	viewMatrix = glm::lookAt(
		position,				// Camera is here
		position + direction,	// and looks here : at the same position, plus "direction"
		up						// Head is up (set to 0,-1,0 to look upside-down)
	);
}


/* --->>> Update <<<--- */
void Player::update(float deltaTime)
{
	updateLight();
}

void Player::updateLight()
{
	light->setPosition(this->getCameraPosition());
}


/* --->>> Getters / Setters <<<--- */
// Insert camera properties to outer shaders
void Player::setCameraUniforms(ShaderProgram* shaderProgram)
{
	shaderProgram->setMat4("ViewMatrix", this->viewMatrix);
	shaderProgram->setMat4("ProjectionMatrix", this->projectionMatrix);
	shaderProgram->setVec3f("cameraPos", this->position);
}

void Player::setCameraPosition(glm::vec3 position)
{
	this->position = position;
}

glm::vec3 Player::getCameraPosition()
{
	return this->position;
}

glm::mat4 Player::getViewMatrix()
{
	return this->viewMatrix;
}

glm::mat4 Player::getProjectionMatrix()
{
	return this->projectionMatrix;
}

glm::vec3 Player::getDirection()
{
	return this->direction;
}

PlayerStats* Player::getStats()
{
	return this->stats;
}

Light::Point* Player::getLight()
{
	return this->light;
}
