#pragma once
#include "src/Game Objects/gameObject.h"
class RespawnPoint
{
public:
	RespawnPoint(GameObject* respawnPointModel, bool isActive);
	~RespawnPoint();

	void drawRespawnPoint(ShaderProgram* shaderProgram);
	void updateRespawnPoint(float deltaTime);

	void setRespawnActivation(bool isActive);

	void setRespawnPointTexture(Texture* texture);

	glm::vec3 getRespawnPointPosition() const;

private:
	GameObject* respawnPointModel;

	glm::vec3 respawnPointPosition;

	float respawnPointRotation = 0;

	bool isActive;
};

