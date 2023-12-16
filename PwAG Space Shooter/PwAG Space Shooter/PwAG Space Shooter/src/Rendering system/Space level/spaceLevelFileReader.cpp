#include "pch.h"
#include "spaceLevelFileReader.h"
#include <fstream>
#include <iostream>

#include "../Rendering system/Space level/gameLevel.h"


/* --->>> Constructors / Destructor <<<--- */
SpaceLevelFileReader::SpaceLevelFileReader() :
	_fileName("res/JSON/levelsInfo.json") {}

SpaceLevelFileReader::~SpaceLevelFileReader()
{}


/* --->>> Level Info <<<--- */
bool SpaceLevelFileReader::loadFile()
{
	std::ifstream file(_fileName);

	if (!file.is_open())
	{
		std::cerr << "Error while openning file: " << _fileName << std::endl;
		return false;
	}

	nlohmann::json JSON;

	file >> JSON;

	for (const auto& item : JSON["levels"])
	{
		GameLevel level(
			item["level"],
			item["enemies"],
			item["bullet_shoot_interval"]["min"],
			item["bullet_shoot_interval"]["max"],
			item["player_shoot_timeout"],
			item["medkits"]
		);

		_levels.push_back(level);
	}
	return true;
}

const GameLevel& SpaceLevelFileReader::getLevelInfo(int levelID) const
{
	return _levels[levelID];
}