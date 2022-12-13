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

	int getAmmunition();
	void shoot();

	bool checkReloadingCooldown(float deltaTime);
	bool checkReloadingTime(float deltaTime);
	void reload(float deltaTime);

	int getPoints();
	void addPoint();

	float getPlayerRadius();

	void updateInput(GameReference gameReference, Keyboard& keyboard, Mouse& mouse, float deltaTime);

	~PlayerStats();

private:
	int hitPoints;
	int maxHitPoints = 100;
	float safeTimeAfterHit = 2.0f;
	float timeAfterLastHit;

	int ammunition;
	int maxAmmunition = 10;

	float reloadingCooldown = 3.5f;
	float timeAfterLastShoot;
	int reloadingSpeed = 2; // ammunition that will be reloaded in 1 second
	float timeAfterLastReload;

	int points = 0;
	int pointsToWin = 5;

	bool alreadyShoot = false;

	float playerRadius = 0.5f;
};
