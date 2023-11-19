#include "pch.h"
#include "PlayerStats.h"

/* --->>> Constructors / Destructor <<<--- */
PlayerStats::PlayerStats()
{
	hitPoints = maxHitPoints;
	timeAfterLastHit = safeTimeAfterHit;
}

PlayerStats::~PlayerStats()
{
}


/* --->>> Health <<<--- */
int PlayerStats::getHitPoints()
{
	return hitPoints;
}

int PlayerStats::getMaxHitPoints()
{
	return maxHitPoints;
}

void PlayerStats::takeDamage(int damage)
{
	hitPoints -= damage;
	checkHitPoints();
}

bool PlayerStats::checkSafeTime(float deltaTime)
{
	if (safeTimeAfterHit <= timeAfterLastHit)
	{
		return true;
	}
	else
	{
		timeAfterLastHit += deltaTime;
		return false;
	}
}

void PlayerStats::checkHitPoints()
{
	if (hitPoints > maxHitPoints)
	{
		hitPoints = maxHitPoints;
	}

	if (hitPoints < 0)
	{
		hitPoints = 0;
	}
}


/* --->>> Shooting <<<--- */
void PlayerStats::shoot()
{
	if (canShoot)
	{
		canShoot = false;
		reloadTime = 0.0f;
	}
}

void PlayerStats::reloadBullet(float deltaTime)
{
	if (!canShoot)
	{
		if (reloadTime < reloadMaxTime)
		{
			reloadTime += deltaTime;
		}
		else
		{
			canShoot = true;
		}
	}
}

bool PlayerStats::canIShoot()
{
	return this->canShoot;
}

float PlayerStats::getReloadMaxTime()
{
	return this->reloadMaxTime;
}

float PlayerStats::getReloadTime()
{
	return this->reloadTime;
}


/* --->>> Points <<<--- */
int PlayerStats::getPoints()
{
	return points;
}

void PlayerStats::addPoint()
{
	points++;
}


/* --->>> Collisions <<<--- */
float PlayerStats::getPlayerRadius()
{
	return playerRadius;
}
