#include "Core/Save.hh"

Save::Save(Level* level) : _level(level), _filename("default.xml")
{
}

Save::Save(Level* level, const std::string filename) : _level(level), _filename(filename)
{
}

Save::~Save()
{
}

void
Save::save(void) const
{
	save(_filename);
}

void
Save::save(const std::string filename) const
{
	Config	cfg;

	cfg["config"]["map"] = saveMap(&_level->_map);
	int	index;
	index = 0;
	for (auto it = _level->_characters.begin(); it != _level->_characters.end(); ++it)
	{
		for (auto subIt = it->second.begin(); subIt != it->second.end(); ++subIt)
		{
			cfg["config"]["characters"]["nb" + std::to_string(index)]["position"] = savePosition(&it->first);
			cfg["config"]["characters"]["nb" + std::to_string(index)]["character"] = saveCharacter(*subIt);
			++index;
		}
	}
	index = 0;
	for (auto it = _level->_players.begin(); it != _level->_players.end(); ++it)
	{
		cfg["config"]["players"]["nb" + std::to_string(index)] = saveCharacter(*it);
		++index;
	}
	index = 0;
	for (auto it = _level->_bombs.begin(); it != _level->_bombs.end(); ++it)
	{
		for (auto subIt = it->second.begin(); subIt != it->second.end(); ++subIt)
		{
			cfg["config"]["bombs"]["nb" + std::to_string(index)]["position"] = savePosition(&it->first);
			cfg["config"]["bombs"]["nb" + std::to_string(index)]["bomb"] = saveBomb(*subIt);
			++index;
		}
	}
	index = 0;
	for (auto it = _level->_items.begin(); it != _level->_items.end(); ++it)
	{
		for (auto subIt = it->second.begin(); subIt != it->second.end(); ++subIt)
		{
			cfg["config"]["items"]["nb" + std::to_string(index)]["position"] = savePosition(&it->first);
			cfg["config"]["items"]["nb" + std::to_string(index)]["item"] = saveBonusItem(*subIt);
			++index;
		}
	}
	cfg["config"]["charactersCount"] = _level->_charactersCount;
	cfg["config"]["playersCount"] = _level->_playersCount;
	cfg["config"]["clock"] = saveClock(&_level->_clock);
	cfg["config"]["secondsElapsed"] = _level->_secondsElapsed;
	index = 0;
	for (auto it = _level->_scores.begin(); it != _level->_scores.end(); ++it)
	{
		cfg["config"]["scores"]["nb" + std::to_string(index)] = saveCharacter(*it);
		++index;
	}
	cfg["config"]["charactersKills"] = _level->_charactersKills;
	//_difficulty
	cfg.exportFile(filename);
}

Config::Param
Save::saveCharacter(const Character* character) const
{
	Config::Param	cfg;

	if (character)
	{
		cfg["id"] = character->_id;
		cfg["isPlayer"] = character->_isPlayer;
		cfg["position"] = savePosition(&character->_position);
		cfg["prevPosition"] = savePosition(&character->_prevPosition);
		cfg["atributes"] = character->_attributes;
		cfg["solid"] = character->_solid;
		cfg["alive"] = character->_alive;
		cfg["killedBy"] = saveBomb(character->_killedBy);
//	cfg["ia"] = saveIA(character->_ia);
		int	index;
		index = 0;
		for (auto it = character->_bombs.begin(); it != character->_bombs.end(); ++it)
		{
			cfg["bombs"]["nb" + std::to_string(index)] = saveBomb(*it);
			++index;
		}
//queuedActions
		cfg["elapsedTime"] = character->_elapsedTime;
		cfg["score"] = character->_score;
	}
	return (cfg);
}

Config::Param
Save::saveMap(const Map* map) const
{
	Config::Param	cfg;

	if (map)
	{
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
				cfg["map"]["nb" + std::to_string(posY)]["nb" + std::to_string(posX)] = saveBlock(*subIt);
				++posX;
			}
			++posY;
		}
	}
	return (cfg);
}

Config::Param
Save::saveBlock(const Block* block) const
{
	Config::Param	cfg;

	if (block)
	{
		Config tmp;
		tmp = savePosition(&block->_position);
		cfg["position"] = tmp;
		cfg["type"] = block->_type;
		cfg["attributes"] = block->_attributes;
		cfg["elapsedTime"] = block->_elapsedTime;
		cfg["visible"] = block->_visible;
		cfg["destructible"] = block->_destructible;
		cfg["solid"] = block->_solid;
		cfg["blockBombs"] = block->_blockBombs;
		cfg["texture"] = block->_texture;
	}
	return (cfg);
}

Config::Param
Save::saveClock(const Clock* clck) const
{
	Config::Param	cfg;

	if (clck)
	{
		//cfg["timer"]
		cfg["seconds"] = clck->_seconds;
		cfg["run"] = clck->_run;
		//cfg["pausedAt"]
		cfg["paused"] = clck->_paused;
	}
	return (cfg);
}

Config::Param
Save::saveBomb(const Bomb* bomb) const
{
	Config::Param	cfg;

	if (bomb)
	{
		cfg["attributes"] = bomb->_attributes;
		cfg["range"] = bomb->_range;
		cfg["position"] = savePosition(&bomb->_position);
		cfg["prevPosition"] = savePosition(&bomb->_prevPosition);
		cfg["prevPosition"] = bomb->_type;
		cfg["clockInit"] = bomb->_clockInit;
		cfg["spawnTime"] = bomb->_spawnTime;
	}
	return (cfg);
}

Config::Param
Save::saveBonusItem(const BonusItem* bonus) const
{
	Config::Param	cfg;

	if (bonus)
	{
		cfg["attributes"] = bonus->_attributes;
		cfg["position"] = savePosition(&bonus->_position);
		cfg["prevPosition"] = savePosition(&bonus->_prevPosition);
		cfg["prevPosition"] = bonus->_type;
		cfg["clockInit"] = bonus->_clockInit;
		cfg["spawnTime"] = bonus->_spawnTime;
	}
	return (cfg);
}

Config::Param
Save::savePosition(const Position<int>* position) const
{
	Config::Param	cfg;

	if (position)
	{
		cfg["x"] = position->_x;
		cfg["y"] = position->_y;
		cfg["z"] = position->_z;
		cfg["isSet"] = position->_isSet;
	}
	return (cfg);
}

Config::Param
Save::savePosition(const Position<double>* position) const
{
	Config::Param	cfg;

	if (position)
	{
		cfg["x"] = position->_x;
		cfg["y"] = position->_y;
		cfg["z"] = position->_z;
		cfg["isSet"] = position->_isSet;
	}
	return (cfg);
}
