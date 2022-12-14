#include "pch.h"
#include "PlayerStats.h"

PlayerStats::PlayerStats()
{
	hitPoints = maxHitPoints;
	timeAfterLastHit = safeTimeAfterHit;
}

int PlayerStats::getHitPoints()
{
	return hitPoints;
}

void PlayerStats::takeDamage(int damage)
{
	/*if (!checkSafeTime(deltaTime))
	{
		return;
	}*/

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


void PlayerStats::shoot()
{
	if (canShoot)
	{
		canShoot = false;
		reloadState = 0.0f;
	}
}

void PlayerStats::reloadBullet(float deltaTime)
{
	if (!canShoot)
	{
		if (reloadState < reloadingTime)
		{
			reloadState += deltaTime;
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

int PlayerStats::getPoints()
{
	return points;
}

void PlayerStats::addPoint()
{
	points++;
}

float  PlayerStats::getPlayerRadius()
{
	return playerRadius;
}


PlayerStats::~PlayerStats()
{

}
