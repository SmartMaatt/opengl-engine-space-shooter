#pragma once
#include "src/Game Objects/gameObject.h"
class Enemy
{
public:
	Enemy(GameObject* enemyModel);
	~Enemy();

	void drawEnemy(ShaderProgram* shaderProgram);
	void updateEnemy(float deltaTime);

	void setEnemyPosition(glm::vec3 position);

	glm::vec3 getEnemyPosition() const;
	glm::vec3 getEnemyPositionWithoutOffset() const;

	void resetEnemyPosition();

	bool canMakeNewMovementDecision();

	void setLastEnemyDirectionX(float dirX);
	void setLastEnemyDirectionY(float dirY);

	float getLastEnemyDirectionX() const;
	float getLastEnemyDirectionY() const;

private:
	float enemyRotation = 0;

	int decisionIterator = 0;

	float lastEnemyDirectionX = 0.0f;
	float lastEnemyDirectionY = 0.0f;

	GameObject* enemyModel;

	glm::vec3 enemyStartPosition;
};

