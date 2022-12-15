#pragma once
#include "pch.h"

class PlayerStats
{
public:
	PlayerStats();

	int getHitPoints();
	void takeDamage(int damage);
	void checkHitPoints();
	bool checkSafeTime(float deltaTime);

	void shoot();
	void reloadBullet(float deltaTime);
	bool canIShoot();

	int getPoints();
	void addPoint();

	float getPlayerRadius();

	~PlayerStats();

private:
	int hitPoints;
	int maxHitPoints = 100;
	float safeTimeAfterHit = 2.0f;
	float timeAfterLastHit;

	float reloadingTime = 8.0f;
	float reloadState = 0.0f;
	bool canShoot = true;

	int points = 0;

	bool alreadyShoot = false;
	float playerRadius = 0.3f;
};
