#include "Core/Save.hh"

Save::Save()
{
}

Save::~Save()
{
}

void
Save::save(const Level* level, const std::string filename)
{
	Config	cfg;

	cfg["map"] = this->saveMap(&level->_map);
	int	index;
	index = 0;
	for (auto it = level->_characters.begin(); it != level->_characters.end(); ++it)
	{
		for (auto subIt = it->second.begin(); subIt != it->second.end(); ++subIt)
		{
			cfg["characters"][std::to_string(index)]["position"] = this->savePosition(&it->first);
			cfg["characters"][std::to_string(index)]["character"] = this->saveCharacter(*subIt);
			++index;
		}
	}
	index = 0;
	for (auto it = level->_players.begin(); it != level->_players.end(); ++it)
	{
		cfg["players"][std::to_string(index)] = this->saveCharacter(*it);
		++index;
	}
	index = 0;
	for (auto it = level->_bombs.begin(); it != level->_bombs.end(); ++it)
	{
		for (auto subIt = it->second.begin(); subIt != it->second.end(); ++subIt)
		{
			cfg["bombs"][std::to_string(index)]["position"] = this->savePosition(&it->first);
			cfg["bombs"][std::to_string(index)]["bomb"] = this->saveBomb(*subIt);
			++index;
		}
	}
	index = 0;
	for (auto it = level->_items.begin(); it != level->_items.end(); ++it)
	{
		for (auto subIt = it->second.begin(); subIt != it->second.end(); ++subIt)
		{
			cfg["items"][std::to_string(index)]["position"] = this->savePosition(&it->first);
			cfg["items"][std::to_string(index)]["item"] = this->saveBonusItem(*subIt);
			++index;
		}
	}
	cfg["charactersCount"] = level->_charactersCount;
	cfg["playersCount"] = level->_playersCount;
	cfg["clock"] = this->saveClock(&level->_clock);
	cfg["secondsElapsed"] = level->_secondsElapsed;
	index = 0;
	for (auto it = level->_scores.begin(); it != level->_scores.end(); ++it)
	{
		cfg["scores"][std::to_string(index)] = this->saveCharacter(*it);
		++index;
	}
	cfg["charactersKills"] = level->_charactersKills;
	cfg.exportFile(filename);
}

Config
Save::saveCharacter(const Character* character)
{
	Config	cfg;

	cfg["nth"] = character->_nth;
	cfg["isPlayer"] = character->_isPlayer;
	cfg["position"] = this->savePosition(&character->_position);
	cfg["prevPosition"] = this->savePosition(&character->_prevPosition);
	cfg["atributes"] = character->_attributes;
	cfg["solid"] = character->_solid;
	cfg["alive"] = character->_alive;
	cfg["killedBy"] = this->saveBomb(character->_killedBy);
//	cfg["ia"] = this->saveIA(character->_ia);
	int	index;
	index = 0;
	for (auto it = character->_bombs.begin(); it != character->_bombs.end(); ++it)
	{
		cfg["bombs"][std::to_string(index)] = this->saveBomb(*it);
		++index;
	}
//queuedActions
	cfg["elapsedTime"] = character->_elapsedTime;
	cfg["score"] = character->_score;
	return (cfg);
}

Config
Save::saveMap(const Map* map)
{
	Config	cfg;

	cfg["width"] = map->_width;
	cfg["height"] = map->_height;

	int	posX;
	int	posY;
	posX = 0;
	posY = 0;
	for (auto it = map->_map.begin(); it != map->_map.end(); ++it)
	{
		for (auto subIt = it->begin(); subIt != it->end(); ++subIt)
		{
			cfg["map"][std::to_string(posY)][std::to_string(posX)] = this->saveBlock(*subIt);
			++posX;
		}
		++posY;
	}
	return (cfg);
}

Config
Save::saveBlock(const Block* block)
{
	Config	cfg;

	cfg["position"] = this->savePosition(&block->_position);
	cfg["type"] = block->_type;
	cfg["attributes"] = block->_attributes;
	cfg["elapsedTime"] = block->_elapsedTime;
	cfg["visible"] = block->_visible;
	cfg["destructible"] = block->_destructible;
	cfg["solid"] = block->_solid;
	cfg["blockBombs"] = block->_blockBombs;
	cfg["texture"] = block->_texture;
	return (cfg);
}

Config
Save::saveClock(const Clock* clock)
{
	Config	cfg;

//	cfg["timer"]
	cfg["seconds"] = clock->_seconds;
	cfg["run"] = clock->_run;
//	cfg["pausedAt"]
	cfg["paused"] = clock->_paused;
	return (cfg);
}

Config
Save::saveBomb(const Bomb* bomb)
{
	Config	cfg;

	cfg["attributes"] = bomb->_attributes;
	cfg["range"] = bomb->_range;
	cfg["position"] = this->savePosition(&bomb->_position);
	cfg["prevPosition"] = this->savePosition(&bomb->_prevPosition);
	cfg["prevPosition"] = bomb->_type;
	cfg["clockInit"] = bomb->_clockInit;
	cfg["spawnTime"] = bomb->_spawnTime;
	return (cfg);
}

Config
Save::saveBonusItem(const BonusItem* bonus)
{
	Config	cfg;

	cfg["attributes"] = bonus->_attributes;
	cfg["position"] = this->savePosition(&bonus->_position);
	cfg["prevPosition"] = this->savePosition(&bonus->_prevPosition);
	cfg["prevPosition"] = bonus->_type;
	cfg["clockInit"] = bonus->_clockInit;
	cfg["spawnTime"] = bonus->_spawnTime;
	return (cfg);
}

Config
Save::savePosition(const Position<int>* position)
{
	Config	cfg;

	cfg["x"] = position->_x;
	cfg["y"] = position->_y;
	cfg["z"] = position->_z;
	cfg["isSet"] = position->_isSet;
	return (cfg);
}

Config
Save::savePosition(const Position<double>* position)
{
	Config	cfg;

	cfg["x"] = position->_x;
	cfg["y"] = position->_y;
	cfg["z"] = position->_z;
	cfg["isSet"] = position->_isSet;
	return (cfg);
}
