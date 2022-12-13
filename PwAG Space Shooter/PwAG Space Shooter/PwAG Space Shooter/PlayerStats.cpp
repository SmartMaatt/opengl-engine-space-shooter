#include "PlayerStats.h"

PlayerStats::PlayerStats()
{
	hitPoints = maxHitPoints;
	ammunition = maxAmmunition;
	timeAfterLastShoot = reloadingCooldown;
	timeAfterLastReload = 1.0f;
}

int PlayerStats::getHitPoints()
{
	return hitPoints;
}

void PlayerStats::takeDamage(int damage)
{
	hitPoints -= damage;
	
	checkHitPoints();
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

int PlayerStats::getAmmunition()
{
	return ammunition;
}

//void PlayerStats::setAmmunition(int currentAmmunitionCount)
//{
//	ammunition = currentAmmunitionCount;
//}

void PlayerStats::shoot()
{
	//setAmmunition(ammunition - 1);
	ammunition--;
	timeAfterLastShoot = 0;
}

//float PlayerStats::getTimeAfterLastShoot()
//{
//	return timeAfterLastShoot;
//}
//
//void PlayerStats::setTimeAfterLastShoot()
//{
//	timeAfterLastShoot = 0;
//}

bool PlayerStats::checkReloadingCooldown(float deltaTime)
{
	if (reloadingCooldown <= timeAfterLastShoot)
	{
		return true;
	}
	else
	{
		timeAfterLastShoot += deltaTime;
		return false;
	}
}

bool PlayerStats::checkReloadingTime(float deltaTime)
{
	if (1.0f <= timeAfterLastReload)
	{
		timeAfterLastReload = 0.0f;
		return true;
	}
	else
	{
		timeAfterLastReload += deltaTime;
		return false;
	}
}

void PlayerStats::reload(float deltaTime)
{
	if (!checkReloadingCooldown(deltaTime))
	{
		return;
	}
	if (!checkReloadingTime(deltaTime))
	{
		return;
	}

	ammunition += reloadingSpeed;
}

int PlayerStats::getPoints()
{
	return points;
}

void PlayerStats::addPoint()
{
	points++;
}

PlayerStats::~PlayerStats()
{

}
