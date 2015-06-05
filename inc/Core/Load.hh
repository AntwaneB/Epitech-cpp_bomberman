#ifndef LOAD_HH
#define LOAD_HH

#include "Core/Config.hh"
#include "Core/Character.hh"
#include "Core/Level.hh"
#include "Core/Map.hh"
#include "Core/Clock.hh"
#include "Core/Item.hh"
#include "Core/BonusItem.hh"
#include "Core/Position.hh"

class	Load
{
public:
	Load(const std::string);
	~Load();

public:
	Level*			load(void) const;

private:
	std::string		_filename;
};

#endif // LOAD_HH
