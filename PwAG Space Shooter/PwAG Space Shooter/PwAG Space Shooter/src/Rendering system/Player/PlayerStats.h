#pragma once
#include "pch.h"

class PlayerStats
{
public:
	// Constructors / Destructor
	PlayerStats();
	~PlayerStats();

	// Health
	int getHitPoints();
	int getMaxHitPoints();
	void takeDamage(int damage);
	void checkHitPoints();
	bool checkSafeTime(float deltaTime);

	// Shooting
	void shoot();
	void reloadBullet(float deltaTime);
	bool canIShoot();
	float getReloadMaxTime();
	float getReloadTime();

	// Points
	int getPoints();
	void addPoint();

	// Collisions
	float getPlayerRadius();

private:
	int hitPoints;
	int maxHitPoints = 100;
	float safeTimeAfterHit = 2.0f;
	float timeAfterLastHit;

	float reloadMaxTime = 8.0f;
	float reloadTime = 0.0f;
	bool canShoot = true;

	int points = 0;

	bool alreadyShoot = false;
	float playerRadius = 0.3f;
};
