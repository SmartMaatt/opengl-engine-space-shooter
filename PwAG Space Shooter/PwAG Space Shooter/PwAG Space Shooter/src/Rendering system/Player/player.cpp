#include "pch.h"
#include "player.h"
#include "GLM/include/gtc/matrix_transform.hpp"

/* --->>> Constructors / Destructor <<<--- */
Player::Player() {}

Player::Player(glm::vec3 startPosition, float reloadTime)
{
	_stats = new PlayerStats();
	_stats->setReloadMaxTime(reloadTime);
	_light = new Light::Point({ 1,0,1 }, { 1,1,1 });

	_position = startPosition;
	_horizontalAngle = 3.14f;
	_verticalAngle = 0.0f;
	_initialFoV = 45.0f;

	_speed = 3.0f;
	_mouseSpeed = 0.0005f;
}

Player::~Player()
{
	delete _stats;
	delete _light;
}


/* --->>> Input <<<--- */
void Player::input(GameReference& gameReference, Keyboard& keyboard, float deltaTime)
{
	_processInput(gameReference, keyboard, deltaTime);
	_updateMatricesFromInput();
}

void Player::_processInput(GameReference& gameReference, Keyboard& keyboard, float deltaTime)
{
	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(gameReference->window, &xpos, &ypos);

	// Reset mouse position for next frame
	glfwSetCursorPos(gameReference->window, Config::g_defaultWidth / 2, Config::g_defaultHeight / 2);

	// Compute new orientation
	_horizontalAngle += _mouseSpeed * float(Config::g_defaultWidth / 2 - xpos);
	_verticalAngle += _mouseSpeed * float(Config::g_defaultHeight / 2 - ypos);

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	_direction = glm::vec3(
		cos(_verticalAngle) * sin(_horizontalAngle),
		sin(_verticalAngle),
		cos(_verticalAngle) * cos(_horizontalAngle)
	);

	// Right vector
	_right = glm::vec3(
		sin(_horizontalAngle - 3.14f / 2.0f),
		0,
		cos(_horizontalAngle - 3.14f / 2.0f)
	);

	// Normalization of direction vector
	if (glm::length(_direction) > 0) {
		_direction = glm::normalize(_direction);
	}

	// Normalization of right vector
	if (glm::length(_right) > 0) {
		_right = glm::normalize(_right);
	}

	// Up vector
	_up = glm::cross(_right, _direction);
	_movementDirection = glm::vec3(0);

	if (keyboard.keyState[static_cast<int>(Keyboard::Key::eKeyW)]) {
		_movementDirection += _direction;
	}

	if (keyboard.keyState[static_cast<int>(Keyboard::Key::eKeyS)]) {
		_movementDirection -= _direction;
	}

	if (keyboard.keyState[static_cast<int>(Keyboard::Key::eKeyA)]) {
		_movementDirection -= _right;
	}

	if (keyboard.keyState[static_cast<int>(Keyboard::Key::eKeyD)]) {
		_movementDirection += _right;
	}

	if (keyboard.keyState[static_cast<int>(Keyboard::Key::eKeySpace)]) {
		_movementDirection += _up;
	}

	if (keyboard.keyState[static_cast<int>(Keyboard::Key::eKeyLeftShift)]) {
		_movementDirection -= _up;
	}

	// Normalization of movement vector
	if (glm::length(_movementDirection) > 0) {
		_movementDirection = glm::normalize(_movementDirection);
	}

	_position += _movementDirection * deltaTime * _speed;
}

void Player::_updateMatricesFromInput()
{
	float FoV = _initialFoV;
	_projectionMatrix = glm::perspective(
		glm::radians(FoV),
		(float)Config::g_defaultWidth / (float)Config::g_defaultHeight,
		0.1f,
		100.0f
	);

	_viewMatrix = glm::lookAt(
		_position,				// Camera is here
		_position + _direction,	// and looks here : at the same position, plus "direction"
		_up						// Head is up (set to 0,-1,0 to look upside-down)
	);
}


/* --->>> Update <<<--- */
void Player::update(float deltaTime)
{
	_updateLight();
}

void Player::_updateLight()
{
	_light->setPosition(getCameraPosition());
}


/* --->>> Getters / Setters <<<--- */
// Insert camera properties to outer shaders
void Player::setCameraUniforms(ShaderProgram* shaderProgram)
{
	shaderProgram->setMat4("ViewMatrix", _viewMatrix);
	shaderProgram->setMat4("ProjectionMatrix", _projectionMatrix);
	shaderProgram->setVec3f("cameraPos", _position);
}

void Player::setCameraPosition(glm::vec3 position)
{
	_position = position;
}

glm::vec3 Player::getCameraPosition()
{
	return _position;
}

glm::mat4 Player::getViewMatrix()
{
	return _viewMatrix;
}

glm::mat4 Player::getProjectionMatrix()
{
	return _projectionMatrix;
}

glm::vec3 Player::getDirection()
{
	return _direction;
}

glm::vec3 Player::getUp()
{
	return _up;
}

PlayerStats* Player::getStats()
{
	return _stats;
}

Light::Point* Player::getLight()
{
	return _light;
}
