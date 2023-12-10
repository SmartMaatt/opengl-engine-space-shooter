#include "pch.h"
#include "gameLevel.h"


/* --->>> Constructors / Destructor <<<--- */
GameLevel::GameLevel(int level, int enemies, float minInterval, float maxInterval, float timeout, int medkits):
	levelID(level),
	enemiesCount(enemies),
	enemiesBulletShootIntervalMin(minInterval),
	enemiesBulletShootIntervalMax(maxInterval),
	playerShootTimeot(timeout),
	medkitsCount(medkits)
{}