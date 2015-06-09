/*
 * File:   Menu.cpp
 * Author: buchse_a
 *
 * Created on May 5, 2015, 8:53 PM
 */

#include <iostream>
#include <fstream>
#include <dirent.h>
#include "Graphics/Menu.hh"
#include "Core/Menu.hh"
#include "Core/Input.hh"
#include "Core/Load.hh"

Menu::Menu(const std::string & filename, const Level * level)
	: _filename(filename), _level(level), _hasSelectable(false)
{
	_actions[KEY_PRESSED] = &Menu::keyPressed;

	_menuActions["NEW_MENU"] = &Menu::actionNewMenu;
	_menuActions["RUN_LEVEL"] = &Menu::actionRunLevel;
	_menuActions["LOAD_LEVEL"] = &Menu::actionLoadLevel;
	_menuActions["SAVE_SCORE"] = &Menu::actionSaveScore;
	_menuActions["EXIT"] = &Menu::actionExit;

	_layout.importFile(_filename);
	if (_layout["content"].isEmpty())
		throw ConfigException("File " + filename + " is not valid");

	this->init();
}

Menu::~Menu()
{
}

Config&
Menu::layout(void)
{
	return _layout;
}

bool
Menu::hasSelectable() const
{
	return (_hasSelectable);
}

void
Menu::run()
{
	this->notify(this, MENU_STARTED);
}

void
Menu::init()
{
	for (auto it = _layout["content"].begin(); it != _layout["content"].end(); ++it)
	{
		if (it->second["is_collection"] == true)
		{
			Config::Param& collection = it->second;

			if (collection["collection"]["type"] == "files")
				this->buildFilesCollection(collection);
			else if (collection["collection"]["type"] == "file_content")
				this->buildFileContentCollection(collection);
		}
		else if (it->second["type"] == "value_only" && it->second["value"]["type"] == "FROM_LEVEL")
		{
			Config::Param& value = it->second["value"];

			this->buildFromLevelValue(value);
		}
	}
	for (auto it = _layout["content"].begin(); it != _layout["content"].end(); ++it)
	{
		_hasSelectable = it->second["selectable"] == true || it->second["selected"] == true ? true : _hasSelectable;
	}
}

void
Menu::buildFilesCollection(Config::Param& collection)
{
	std::string folder = collection["collection"]["folder"];

	DIR* dir;
	if ((dir = opendir(folder.c_str())) != NULL)
	{
		int i = 0;

		int y = collection["position"]["min_y"];
		int x = collection["position"]["min_x"];
		struct dirent* file;
		while ((file = readdir(dir)) != NULL)
		{
			std::string filename = file->d_name;
			if (filename.substr(filename.find_last_of(".") + 1) == static_cast<std::string>(collection["collection"]["files_ext"]))
			{
				Config::Param element;
				element["type"] = "value_only";
				element["order"] = i + 1;
				element["selectable"] = true;
				element["selected"] = collection["selected"] == true && i == 0 ? true : false;
				element["has_value"] = true;
				element["value"]["value"] = filename.substr(0, filename.find_last_of("."));
				element["value"]["size"] = collection["collection"]["font_size"];
				element["value"]["y"] = y;
				element["value"]["x"] = x;
				element["cursor"]["position"]["x"] = static_cast<int>(element["value"]["x"]) - 35;
				element["cursor"]["position"]["y"] = static_cast<int>(element["value"]["y"]) + 20;
				element["action"]["name"] = static_cast<std::string>(collection["action"]["name"]);
				element["action"]["param"] = folder + filename;

				std::string key = collection["id"];
				key += std::to_string(++i);
				_layout["content"].insert(std::map<std::string, Config::Param>::value_type(key, element));

				y = y + static_cast<int>(collection["collection"]["font_size"]);
				if (y >= static_cast<int>(collection["position"]["max_y"]))
				{
					x = static_cast<int>(collection["position"]["min_x"])
						+ (static_cast<int>(collection["position"]["max_x"]) - static_cast<int>(collection["position"]["min_x"])) / static_cast<int>(collection["cols"]);
					y = collection["position"]["min_y"];
				}
			}
		}
		closedir(dir);
	}
	collection["selected"] = false;
}

void
Menu::buildFileContentCollection(Config::Param& collection)
{
	std::ifstream file;

	file.open(collection["collection"]["file"]);
	if (!file.is_open())
		throw ConfigException("Couldn't open file, cannot build menu content.");

	int y = collection["position"]["min_y"];
	int x = collection["position"]["min_x"];
	int i = 0;

	if (collection["collection"]["sorted"] != true)
	{
		std::string col1; std::string col2;
		while (i < static_cast<int>(collection["collection"]["limit"]) && file >> col1 >> col2)
		{
			Config::Param element;
			element["type"] = "value_only";
			element["order"] = i + 1;
			element["selectable"] = collection["selectable"] == true ? true : false;
			element["selected"] = collection["selected"] == true && i == 0 ? true : false;
			element["has_value"] = true;
			element["value"]["value"] = col1 + " " + col2;
			element["value"]["size"] = collection["collection"]["font_size"];
			element["value"]["y"] = y;
			element["value"]["x"] = x;
			element["cursor"]["position"]["x"] = static_cast<int>(element["value"]["x"]) - 35;
			element["cursor"]["position"]["y"] = static_cast<int>(element["value"]["y"]) + 35;

			std::string key = collection["id"];
			key += std::to_string(++i);
			_layout["content"].insert(std::map<std::string, Config::Param>::value_type(key, element));

			y = y + static_cast<int>(collection["collection"]["font_size"]);
			if (y >= static_cast<int>(collection["position"]["max_y"]))
			{
				x = static_cast<int>(collection["position"]["min_x"])
					+ (static_cast<int>(collection["position"]["max_x"]) - static_cast<int>(collection["position"]["min_x"])) / static_cast<int>(collection["cols"]);
				y = collection["position"]["min_y"];
			}
		}
	}
	else
	{
		std::vector<std::pair<int, std::string> > values;

		std::string value; int key;
		while (file >> value >> key)
			values.push_back(std::make_pair(key, value));
		std::sort(values.begin(), values.end(), [](const std::pair<int, std::string>& p1, const std::pair<int, std::string>& p2) -> bool {
			return (p1.first > p2.first);
		});

		for (auto it = values.begin(); i < static_cast<int>(collection["collection"]["limit"]) && it != values.end(); ++it)
		{
			Config::Param element;
			element["type"] = "value_only";
			element["order"] = i + 1;
			element["selectable"] = collection["selectable"] == true ? true : false;
			element["selected"] = collection["selected"] == true && i == 0 ? true : false;
			element["has_value"] = true;
			element["value"]["value"] = it->second + " " + std::to_string(it->first);
			element["value"]["size"] = collection["collection"]["font_size"];
			element["value"]["y"] = y;
			element["value"]["x"] = x;
			element["cursor"]["position"]["x"] = static_cast<int>(element["value"]["x"]) - 35;
			element["cursor"]["position"]["y"] = static_cast<int>(element["value"]["y"]) + 35;

			std::string key = collection["id"];
			key += std::to_string(++i);
			_layout["content"].insert(std::map<std::string, Config::Param>::value_type(key, element));

			y = y + static_cast<int>(collection["collection"]["font_size"]);
			if (y >= static_cast<int>(collection["position"]["max_y"]))
			{
				x = static_cast<int>(collection["position"]["min_x"])
					+ (static_cast<int>(collection["position"]["max_x"]) - static_cast<int>(collection["position"]["min_x"])) / static_cast<int>(collection["cols"]);
				y = collection["position"]["min_y"];
			}
		}
	}

	collection["selected"] = false;
}

void
Menu::buildFromLevelValue(Config::Param& value)
{
	std::string valueStr;

	if (value["key"] == "WINNER_ID")
		valueStr = std::to_string(_level->winner()->id());

	value["value"] = valueStr;
}

void
Menu::keyPressed(Subject* entity)
{
	Input*	input = safe_cast<Input*>(entity);

	std::map<Input::Key, void (Menu::*)(Input::Key)> actions;
	actions[Input::SPACE] = &Menu::runLine;
	actions[Input::ENTER] = &Menu::runLine;
	actions[Input::ESC] = &Menu::quit;
	if (_layout["controls_inverted"] != true)
	{
		actions[Input::UP] = &Menu::changeLine;
		actions[Input::DOWN] = &Menu::changeLine;
		actions[Input::LEFT] = &Menu::changeValue;
		actions[Input::RIGHT] = &Menu::changeValue;
	}
	else
	{
		actions[Input::LEFT] = &Menu::changeLine;
		actions[Input::RIGHT] = &Menu::changeLine;
		actions[Input::UP] = &Menu::changeValue;
		actions[Input::DOWN] = &Menu::changeValue;
	}

	if (actions.find(input->genericKey()) != actions.end())
		(this->*(actions[input->genericKey()]))(input->genericKey());

	this->notify(this, MENU_UPDATED);
}

void
Menu::changeLine(Input::Key key)
{
	if (!_hasSelectable)
		return;

	size_t count = 0;

	Config::Param* active = NULL;
	for (auto it = _layout["content"].begin(); it != _layout["content"].end(); ++it)
	{
		if (it->second["selected"] == true)
			active = &(it->second);
		if (it->second["selectable"] == true)
			count++;
	}
	if (!active)
		return;

	for (auto it = _layout["content"].begin(); it != _layout["content"].end(); ++it)
	{
		if (key == Input::UP || (_layout["controls_inverted"] == true && key == Input::LEFT))
		{
			if (&(it->second) != active
				&& it->second["selectable"] == true
				&& (it->second["order"] == static_cast<int>((*active)["order"]) - 1 || ((*active)["order"] == 1 && static_cast<size_t>(it->second["order"]) == count)))
			{
				it->second["selected"] = true;
			}
		}
		else if (key == Input::DOWN || (_layout["controls_inverted"] == true && key == Input::RIGHT))
		{
			if (&(it->second) != active
					&& it->second["selectable"] == true
					&& (it->second["order"] == static_cast<int>((*active)["order"]) + 1 || (static_cast<size_t>((*active)["order"]) == count
																												  && static_cast<size_t>(it->second["order"]) == 1)))
			{
				it->second["selected"] = true;
			}
		}
	}
	(*active)["selected"] = false;
}

void
Menu::changeValue(Input::Key key)
{
	Config::Param* active = NULL;
	for (auto it = _layout["content"].begin(); it != _layout["content"].end(); ++it)
	{
		if (it->second["selected"] == true)
			active = &(it->second);
	}

	if (active && (*active)["has_value"] == true
		&& (static_cast<std::string>((*active)["value"]["min"]).empty() == false
			|| static_cast<std::string>((*active)["value"]["max"]).empty() == false))
	{
		if ((*active)["value"]["type"] == "ASCII")
		{
			char newValue = (*active)["value"]["value"];
			newValue = key == Input::LEFT || (_layout["controls_inverted"] == true && key == Input::UP) ? newValue - 1 : newValue + 1;
			newValue = (*active)["value"]["min"] > newValue ? (*active)["value"]["max"] : newValue;
			newValue = (*active)["value"]["max"] < newValue ? (*active)["value"]["min"] : newValue;

			std::string newValueStr;
			newValueStr += newValue;
			(*active)["value"]["value"] = newValueStr;
		}
		else
		{
			int newValue = (*active)["value"]["value"];
			newValue = key == Input::LEFT || (_layout["controls_inverted"] == true && key == Input::UP) ? newValue - 1 : newValue + 1;
			newValue = (*active)["value"]["min"] > newValue ? (*active)["value"]["max"] : newValue;
			newValue = (*active)["value"]["max"] < newValue ? (*active)["value"]["min"] : newValue;

			(*active)["value"]["value"] = newValue;
		}
	}
}

void
Menu::runLine(Input::Key key __attribute__((unused)))
{
	Config::Param* active = NULL;
	for (auto it = _layout["content"].begin(); it != _layout["content"].end(); ++it)
	{
		if (it->second["selected"] == true)
			active = &(it->second);
	}

	if (active && _menuActions.find((*active)["action"]["name"]) != _menuActions.end())
		(this->*(_menuActions[(*active)["action"]["name"]]))((*active)["action"]["param"]);
}

void
Menu::quit(Input::Key key __attribute__((unused)))
{
	this->notify(this, EXIT_TRIGGERED);
}

void
Menu::actionNewMenu(const std::string& param)
{
	this->notify(new Menu(param), MENU_STARTED);
}

void
Menu::actionLoadLevel(const std::string& param)
{
	this->notify(this, MENU_EXITED);

	Load	load(param);
	Level* level = load.load();
	this->notify(level, LEVEL_GENERATED);
}

void
Menu::actionRunLevel(const std::string& param __attribute__((unused)))
{
	size_t width = _layout["content"]["width"]["value"]["value"];
	size_t height = _layout["content"]["height"]["value"]["value"];
	size_t iaCount = _layout["content"]["ias"]["value"]["value"];
	size_t playerCount = _layout["content"]["players"]["value"]["value"];
	size_t difficulty = _layout["content"]["difficulty"]["value"]["value"];

	std::cout << "Generating new level with the following settings :" << std::endl;
	std::cout << "- Width : " << width << std::endl;
	std::cout << "- Height : " <<  height << std::endl;
	std::cout << "- IA Count : " <<  iaCount << std::endl;
	std::cout << "- Player Count : " <<  playerCount << std::endl;
	std::cout << "- Difficulty : " <<  difficulty << std::endl;
	std::cout << std::endl;

	this->notify(this, MENU_EXITED);
	this->notify(new Level(width, height, iaCount + playerCount, playerCount, static_cast<IA::Difficulty>(difficulty)), LEVEL_GENERATED);
}

void
Menu::actionSaveScore(const std::string& param __attribute__((unused)))
{
	if (_level == NULL)
		throw ConfigException("Invalid menu");

	std::string namePlayer;
	namePlayer += static_cast<char>(_layout["content"]["letter_1"]["value"]["value"]);
	namePlayer += static_cast<char>(_layout["content"]["letter_2"]["value"]["value"]);
	namePlayer += static_cast<char>(_layout["content"]["letter_3"]["value"]["value"]);

	std::ofstream file;
	file.open("config/scores", std::ios::app);
	if (file.is_open())
	{
		file << namePlayer << " " << _level->winner()->score() << "\n";
		file.close();
	}
	else
		std::cerr << "Error while saving score :(" << std::endl;

	this->notify(this, MENU_EXITED);
	this->notify(new Menu("./menus/scores.xml"), MENU_STARTED);
}

void
Menu::actionExit(const std::string& param __attribute__((unused)))
{
	this->quit(Input::ESC);
}
