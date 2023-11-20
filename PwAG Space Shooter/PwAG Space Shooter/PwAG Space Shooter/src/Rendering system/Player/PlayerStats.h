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
	int _hitPoints;
	int _maxHitPoints = 100;
	float _safeTimeAfterHit = 2.0f;
	float _timeAfterLastHit;

	float _reloadMaxTime = 8.0f;
	float _reloadTime = 0.0f;
	bool _canShoot = true;

	int _points = 0;

	bool _alreadyShoot = false;
	float _playerRadius = 0.3f;
};
