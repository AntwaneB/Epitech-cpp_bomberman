#ifndef SAVE_HH
#define SAVE_HH

#include "Core/Config.hh"
#include "Core/Character.hh"
#include "Core/Level.hh"
#include "Core/Map.hh"
#include "Core/Clock.hh"
#include "Core/Item.hh"
#include "Core/BonusItem.hh"
#include "Core/Position.hh"

class	Save
{
public:
	Save();
	~Save();

private:
	Config			saveCharacter(const Character*);
	Config			saveMap(const Map*);
	Config			saveBlock(const Block*);
	Config			saveClock(const Clock*);
	Config			saveBomb(const Bomb*);
	Config			saveBonusItem(const BonusItem*);
	Config			savePosition(const Position<int>*);
	Config			savePosition(const Position<double>*);
//	Config			saveIA(const IA::IA*);

public:
	void			save(const Level*, const std::string);
};

#endif // SAVE_HH
