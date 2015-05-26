/**
 * Copyright 2015 Antoine Buchser
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * 	 http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iostream>
#include <stdexcept>
#include "Core/Config.hh"
#include "pugixml.hpp"
#include "Exception.hpp"

Config::Config()
{
}

Config&
Config::operator=(Config::Param const & o)
{
	_params = o;

	return (*this);
}

Config::~Config()
{
}

Config::Param&	Config::operator [](const std::string& key)
{
	if (_params.find(key) == _params.end())
		_params.insert(std::map<std::string, Param>::value_type(key, Param("")));

	return (_params.find(key)->second);
}

Config::Param&	Config::operator [](const char key[])
{
	return (this->operator[](std::string(key)));
}
/*
Config::Param const &	Config::operator [](const std::string& key) const
{
	return (_params.find(key)->second);
}

Config::Param const & Config::operator [](const char key[]) const
{
	return (this->operator[](std::string(key)));
}
*/
Config::Param::Param(const std::string & value)
	: _status(Config::Param::VALUE), _value(value)
{
}

Config::Param::Param(const std::map<std::string, Param>& map)
	: _status(Config::Param::MAP), _map(map)
{
}

Config::Param::Param()
{
}

Config::Param& Config::Param::operator [](const std::string& key)
{
	if (_map.find(key) == _map.end())
	{
		_map.insert(std::map<std::string, Param>::value_type(key, Param("")));
	}

	_status = Config::Param::MAP;

	return (_map.find(key)->second);
}

Config::Param& Config::Param::operator [](const char key[])
{
	return (this->operator[](std::string(key)));
}
/*
Config::Param const & Config::Param::operator [](const std::string& key) const
{
	return (_map.find(key)->second);
}

Config::Param const & Config::Param::operator [](const char key[]) const
{
	return (this->operator[](std::string(key)));
}
*/
Config::Param& Config::Param::operator = (bool value)
{
	_map.clear();
	_status = Config::Param::VALUE;

	_value = value ? "true" : "false";

	return (*this);
}

Config::Param& Config::Param::operator = (char value)
{
	_map.clear();
	_status = Config::Param::VALUE;

	_value = std::to_string(value);

	return (*this);
}

Config::Param& Config::Param::operator = (short value)
{
	_map.clear();
	_status = Config::Param::VALUE;

	_value = std::to_string(value);

	return (*this);
}

Config::Param& Config::Param::operator = (int value)
{
	_map.clear();
	_status = Config::Param::VALUE;

	_value = std::to_string(value);

	return (*this);
}

Config::Param& Config::Param::operator = (long value)
{
	_map.clear();
	_status = Config::Param::VALUE;

	_value = std::to_string(value);

	return (*this);
}

Config::Param& Config::Param::operator = (double value)
{
	_map.clear();
	_status = Config::Param::VALUE;

	_value = std::to_string(value);

	return (*this);
}

Config::Param& Config::Param::operator = (float value)
{
	_map.clear();
	_status = Config::Param::VALUE;

	_value = std::to_string(value);

	return (*this);
}

Config::Param& Config::Param::operator = (std::string const & value)
{
	_map.clear();
	_status = Config::Param::VALUE;

	_value = value;

	return (*this);
}

Config::Param& Config::Param::operator = (const char value[])
{
	_map.clear();
	_status = Config::Param::VALUE;

	_value = value;

	return (*this);
}

Config::Param::operator bool (void) const
{
	if (_status == Config::Param::MAP)
		throw std::runtime_error("Current index is not a valid value");

	return (_value == "true");
}

Config::Param::operator char (void) const
{
	if (_status == Config::Param::MAP)
		throw std::runtime_error("Current index is not a valid value");

	return (std::stoi(_value));
}

Config::Param::operator short (void) const
{
	if (_status == Config::Param::MAP)
		throw std::runtime_error("Current index is not a valid value");

	return (std::stoi(_value));
}

Config::Param::operator int (void) const
{
	if (_status == Config::Param::MAP)
		throw std::runtime_error("Current index is not a valid value");

	return (std::stoi(_value));
}

Config::Param::operator long (void) const
{
	if (_status == Config::Param::MAP)
		throw std::runtime_error("Current index is not a valid value");

	return (std::stol(_value));
}

Config::Param::operator double (void) const
{
	if (_status == Config::Param::MAP)
		throw std::runtime_error("Current index is not a valid value");

	return (std::stod(_value));
}

Config::Param::operator float (void) const
{
	if (_status == Config::Param::MAP)
		throw std::runtime_error("Current index is not a valid value");

	return (static_cast<float>(std::stod(_value)));
}

Config::Param::operator std::string (void) const
{
	if (_status == Config::Param::MAP)
		throw std::runtime_error("Current index is not a valid value");

	return (_value);
}


Config::Param::operator unsigned char (void) const
{
	if (_status == Config::Param::MAP)
		throw std::runtime_error("Current index is not a valid value");

	return (std::stoi(_value));
}

Config::Param::operator unsigned short (void) const
{
	if (_status == Config::Param::MAP)
		throw std::runtime_error("Current index is not a valid value");

	return (std::stoi(_value));
}

Config::Param::operator unsigned int (void) const
{
	if (_status == Config::Param::MAP)
		throw std::runtime_error("Current index is not a valid value");

	return (std::stoi(_value));
}

Config::Param::operator unsigned long (void) const
{
	if (_status == Config::Param::MAP)
		throw std::runtime_error("Current index is not a valid value");

	return (std::stol(_value));
}

std::map<std::string, Config::Param>::iterator	Config::Param::find(const std::string & key)
{
	return (_map.find(key));
}

std::map<std::string, Config::Param>::iterator	Config::Param::begin(void)
{
	return (_map.begin());
}

std::map<std::string, Config::Param>::iterator	Config::Param::end(void)
{
	return (_map.end());
}
/*
std::map<std::string, Config::Param>::const_iterator	Config::Param::find(const std::string & key) const
{
	return (_map.find(key));
}

std::map<std::string, Config::Param>::const_iterator	Config::Param::end(void) const
{
	return (_map.end());
}
*/
void	Config::Param::insert(std::map<std::string, Param>::value_type insert)
{
	_map.insert(insert);
}

const std::string	Config::Param::toXML(void) const
{
	std::string	res;

	res = "";
	if (_status == Status::VALUE)
		res = _value;
	else
		for(std::map<std::string, Param>::const_iterator it = _map.begin(); it != _map.end(); it++)
			res += "<" + it->first + ">" + it->second.toXML() + "</" + it->first + ">";
	return (res);
}

bool Config::Param::operator == (bool o) { return (static_cast<bool>(*this) == o); }
bool Config::Param::operator == (char o) { return (static_cast<char>(*this) == o); }
bool Config::Param::operator == (short o) { return (static_cast<short>(*this) == o); }
bool Config::Param::operator == (int o) { return (static_cast<int>(*this) == o); }
bool Config::Param::operator == (long o) { return (static_cast<long>(*this) == o); }
bool Config::Param::operator == (double o) { return (static_cast<double>(*this) == o); }
bool Config::Param::operator == (float o) { return (static_cast<float>(*this) == o); }
bool Config::Param::operator == (std::string const & o) { return (static_cast<std::string>(*this) == o); }
bool Config::Param::operator == (const char o[]) { return (static_cast<std::string>(*this) == std::string(o)); }
bool Config::Param::operator != (bool o) { return (static_cast<bool>(*this) != o); }
bool Config::Param::operator != (char o) { return (static_cast<char>(*this) != o); }
bool Config::Param::operator != (short o) { return (static_cast<short>(*this) != o); }
bool Config::Param::operator != (int o) { return (static_cast<int>(*this) != o); }
bool Config::Param::operator != (long o) { return (static_cast<long>(*this) != o); }
bool Config::Param::operator != (double o) { return (static_cast<double>(*this) != o); }
bool Config::Param::operator != (float o) { return (static_cast<float>(*this) != o); }
bool Config::Param::operator != (std::string const & o) { return (static_cast<std::string>(*this) != o); }
bool Config::Param::operator != (const char o[]) { return (static_cast<std::string>(*this) != std::string(o)); }
bool Config::Param::operator <= (bool o) { return (static_cast<bool>(*this) <= o); }
bool Config::Param::operator <= (char o) { return (static_cast<char>(*this) <= o); }
bool Config::Param::operator <= (short o) { return (static_cast<short>(*this) <= o); }
bool Config::Param::operator <= (int o) { return (static_cast<int>(*this) <= o); }
bool Config::Param::operator <= (long o) { return (static_cast<long>(*this) <= o); }
bool Config::Param::operator <= (double o) { return (static_cast<double>(*this) <= o); }
bool Config::Param::operator <= (float o) { return (static_cast<float>(*this) <= o); }
bool Config::Param::operator < (bool o) { return (static_cast<bool>(*this) < o); }
bool Config::Param::operator < (char o) { return (static_cast<char>(*this) < o); }
bool Config::Param::operator < (short o) { return (static_cast<short>(*this) < o); }
bool Config::Param::operator < (int o) { return (static_cast<int>(*this) < o); }
bool Config::Param::operator < (long o) { return (static_cast<long>(*this) < o); }
bool Config::Param::operator < (double o) { return (static_cast<double>(*this) < o); }
bool Config::Param::operator < (float o) { return (static_cast<float>(*this) < o); }
bool Config::Param::operator >= (bool o) { return (static_cast<bool>(*this) >= o); }
bool Config::Param::operator >= (char o) { return (static_cast<char>(*this) >= o); }
bool Config::Param::operator >= (short o) { return (static_cast<short>(*this) >= o); }
bool Config::Param::operator >= (int o) { return (static_cast<int>(*this) >= o); }
bool Config::Param::operator >= (long o) { return (static_cast<long>(*this) >= o); }
bool Config::Param::operator >= (double o) { return (static_cast<double>(*this) >= o); }
bool Config::Param::operator >= (float o) { return (static_cast<float>(*this) >= o); }
bool Config::Param::operator > (bool o) { return (static_cast<bool>(*this) > o); }
bool Config::Param::operator > (char o) { return (static_cast<char>(*this) > o); }
bool Config::Param::operator > (short o) { return (static_cast<short>(*this) > o); }
bool Config::Param::operator > (int o) { return (static_cast<int>(*this) > o); }
bool Config::Param::operator > (long o) { return (static_cast<long>(*this) > o); }
bool Config::Param::operator > (double o) { return (static_cast<double>(*this) > o); }
bool Config::Param::operator > (float o) { return (static_cast<float>(*this) > o); }

bool	Config::Param::hasChild(void) const
{
	return (_status == VALUE);
}

std::map<std::string, Config::Param>::iterator	Config::find(const std::string & key)
{
	return (_params.find(key));
}

std::map<std::string, Config::Param>::iterator	Config::begin(void)
{
	return (_params.begin());
}

std::map<std::string, Config::Param>::iterator	Config::end(void)
{
	return (_params.end());
}

const std::string	Config::toXML(void) const
{
	return (_params.toXML());
}

std::ostream&	operator << (std::ostream& os, const Config& cnf)
{
	os << cnf.toXML();

	return (os);
}

std::ostream&	operator << (std::ostream& os, const Config::Param& prm)
{
	os << prm.toXML();

	return (os);
}

Config::Param	Config::fillParams(pugi::xml_node node, Config::Param params, int depth)
{
	std::string	key;
	std::string	subKey;

	if (node != NULL)
	{
		if (node.attribute("name"))
			key = node.attribute("name").value();
		else
			key = std::string(node.name());
		if (!std::string(node.child_value()).size())
			for (pugi::xml_node subNode = node.first_child(); subNode != node.last_child().next_sibling(); subNode = subNode.next_sibling())
			{
				if (subNode.attribute("name"))
					subKey = std::string(subNode.attribute("name").value());
				else
					subKey = subNode.name();
				params[key] = this->fillParams(subNode, params[key], depth + 1);
			}
		else
			params[key] = node.child_value();
	}
	return (params);
}

void	Config::importFile(std::string const & filename)
{
	pugi::xml_document	file;

	pugi::xml_parse_result	result = file.load_file(filename.c_str());
	if (!result)
		throw ConfigException("Invalid file.");
	_params = (fillParams(file.first_child(), _params, 0))["config"];
}

void	Config::exportFile(std::string const & filename) const
{
	pugi::xml_document	file;

	file.load_string(_params.toXML().c_str());
	file.save_file(filename.c_str());
}
/*
int	main()
{
	Config cfg;

	cfg.importFile("./menus/main.xml");

	auto locate = cfg.find("title");
	if (locate != cfg.end())
	{
		std::cout << locate->first << std::endl;
		std::cout << cfg[locate->first] << std::endl;
	}

	for (auto it = cfg.begin(); it != cfg.end(); ++it)
	{
		if (it->second.hasChild())
		{
			std::cout << "Values :";
			std::cout << cfg[it->first] << std::endl;
		}
		else
		{
			std::cout << "Node :";
			std::cout << it->first << std::endl;
		}
	}
}
*/
