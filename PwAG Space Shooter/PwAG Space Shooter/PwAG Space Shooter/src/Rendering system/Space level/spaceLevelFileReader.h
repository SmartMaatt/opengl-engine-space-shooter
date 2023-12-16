#pragma once
#include "../Rendering system/Space level/gameLevel.h"

class SpaceLevelFileReader
{
private:
	std::string _fileName;
	std::vector<GameLevel> _levels;

public:
	// Constructors / Destructor
	SpaceLevelFileReader();
	~SpaceLevelFileReader();

	// File Info
	bool loadFile();
	const GameLevel& getLevelInfo(int levelID) const;
};