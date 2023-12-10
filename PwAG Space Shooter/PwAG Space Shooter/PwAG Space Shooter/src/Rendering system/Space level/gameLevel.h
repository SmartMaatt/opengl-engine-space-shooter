#pragma once


class GameLevel
{
public:
	// Level Info
	int levelID;
	int enemiesCount;
	float enemiesBulletShootIntervalMin;
	float enemiesBulletShootIntervalMax;
	float playerShootTimeot;
	int medkitsCount;

	// Constructors / Destructor
	GameLevel(int level, int enemies, float minInterval, float maxInterval, float timeout, int medkits);
};