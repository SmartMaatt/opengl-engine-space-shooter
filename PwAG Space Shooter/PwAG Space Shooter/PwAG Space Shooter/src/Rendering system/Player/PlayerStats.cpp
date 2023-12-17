#include "pch.h"
#include "PlayerStats.h"

/* --->>> Constructors / Destructor <<<--- */
PlayerStats::PlayerStats()
{
	_hitPoints = _maxHitPoints;
	_timeAfterLastHit = _safeTimeAfterHit;
}

PlayerStats::~PlayerStats()
{
}


/* --->>> Health <<<--- */
int PlayerStats::getHitPoints()
{
	return _hitPoints;
}

int PlayerStats::getMaxHitPoints()
{
	return _maxHitPoints;
}

void PlayerStats::takeDamage(int damage)
{
	_hitPoints -= damage;
	checkHitPoints();
}

void PlayerStats::heal(int healing)
{
	_hitPoints += healing;
	checkHitPoints();
}

bool PlayerStats::checkSafeTime(float deltaTime)
{
	if (_safeTimeAfterHit <= _timeAfterLastHit)
	{
		return true;
	}
	else
	{
		_timeAfterLastHit += deltaTime;
		return false;
	}
}

void PlayerStats::checkHitPoints()
{
	_hitPoints = glm::clamp(_hitPoints, 0, _maxHitPoints);
}


/* --->>> Shooting <<<--- */
void PlayerStats::shoot()
{
	if (_canShoot)
	{
		_canShoot = false;
		_reloadTime = 0.0f;
	}
}

void PlayerStats::reloadBullet(float deltaTime)
{
	if (!_canShoot)
	{
		if (_reloadTime < _reloadMaxTime)
		{
			_reloadTime += deltaTime;
		}
		else
		{
			_canShoot = true;
		}
	}
}

bool PlayerStats::canIShoot()
{
	return _canShoot;
}

float PlayerStats::getReloadMaxTime()
{
	return _reloadMaxTime;
}

void PlayerStats::setReloadMaxTime(float time)
{
	_reloadMaxTime = time;
}

float PlayerStats::getReloadTime()
{
	return _reloadTime;
}


/* --->>> Collisions <<<--- */
float PlayerStats::getPlayerRadius()
{
	return _playerRadius;
}
