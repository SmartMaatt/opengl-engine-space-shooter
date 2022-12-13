#include "pch.h"
#include "PlayerStats.h"

PlayerStats::PlayerStats()
{
	hitPoints = maxHitPoints;
	ammunition = maxAmmunition;
	timeAfterLastShoot = reloadingCooldown;
	timeAfterLastReload = 1.0f;
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

int PlayerStats::getAmmunition()
{
	return ammunition;
}

void PlayerStats::shoot()
{
	if (alreadyShoot ||ammunition == 0)
	{
		return;
	}

	alreadyShoot = true;
	ammunition--;
	timeAfterLastShoot = 0;
}

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
	if (ammunition >= maxAmmunition)
	{
		ammunition = maxAmmunition;
		return;
	}

	ammunition += reloadingSpeed;

	std::cout << "Ammunition reloading: " << this->getAmmunition() << std::endl;
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

void PlayerStats::updateInput(GameReference gameReference, Keyboard& keyboard, Mouse& mouse, float deltaTime)
{
	if (keyboard.keyState[static_cast<int>(Keyboard::Key::eKeyF)])
	{
		this->shoot();
	}
	else
	{
		alreadyShoot = false;
	}
}

PlayerStats::~PlayerStats()
{

}
