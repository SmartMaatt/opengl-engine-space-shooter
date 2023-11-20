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
	if (_hitPoints > _maxHitPoints)
	{
		_hitPoints = _maxHitPoints;
	}

	if (_hitPoints < 0)
	{
		_hitPoints = 0;
	}
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

float PlayerStats::getReloadTime()
{
	return _reloadTime;
}


/* --->>> Points <<<--- */
int PlayerStats::getPoints()
{
	return _points;
}

void PlayerStats::addPoint()
{
	_points++;
}


/* --->>> Collisions <<<--- */
float PlayerStats::getPlayerRadius()
{
	return _playerRadius;
}
