#include "pch.h"
#include "enemy.h"

Enemy::Enemy(GameObject* enemyModel)
{
	this->enemyModel = enemyModel;
	this->enemyStartPosition = enemyModel->getPosition();
}

Enemy::~Enemy()
{
	delete this->enemyModel;
}


void Enemy::drawEnemy(ShaderProgram* shaderProgram)
{
	this->enemyModel->draw(shaderProgram);
}

void Enemy::updateEnemy(float deltaTime)
{
	std::vector<GLfloat> offsetEnemy = this->enemyModel->getOffsets();

	glm::vec3 pos = this->enemyModel->getPosition();

	if (offsetEnemy.size() >= 3) {
			this->enemyModel->setOrigin(glm::vec3(offsetEnemy[0] + pos.x, offsetEnemy[1] + pos.y, offsetEnemy[2] + pos.z));
			this->enemyModel->setRotation(glm::vec3(0, enemyRotation += deltaTime *25, 0.f));
	}
}

void Enemy::setEnemyPosition(glm::vec3 position) {
	this->enemyModel->setPosition(position);
}

glm::vec3 Enemy::getEnemyPosition() const
{
	std::vector<GLfloat> offsetEnemy = this->enemyModel->getOffsets();

	glm::vec3 pos = this->enemyModel->getPosition();

	if (offsetEnemy.size() >= 3) {
		return glm::vec3(offsetEnemy[0] + pos.x, offsetEnemy[1] + pos.y, offsetEnemy[2] + pos.z);
	}

	return glm::vec3(-1, -1, -1);
}

glm::vec3 Enemy::getEnemyPositionWithoutOffset() const {
	return this->enemyModel->getPosition();
}

void Enemy::resetEnemyPosition() {
	this->enemyModel->setPosition(this->enemyStartPosition);
}

bool Enemy::canMakeNewMovementDecision()
{
	decisionIterator++;

	if (decisionIterator >= 100) {
		decisionIterator = 0;

		return true;
	}

	return false;
}

void Enemy::setLastEnemyDirectionX(float dirX)
{
	this->lastEnemyDirectionX = dirX;
}

void Enemy::setLastEnemyDirectionY(float dirY)
{
	this->lastEnemyDirectionY = dirY;
}

float Enemy::getLastEnemyDirectionX() const
{
	return this->lastEnemyDirectionX;
}

float Enemy::getLastEnemyDirectionY() const
{
	return this->lastEnemyDirectionY;
}
