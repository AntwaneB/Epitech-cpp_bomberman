#ifndef SAVE_HH
#define SAVE_HH

#include "Core/Config.hh"
#include "Core/Character.hh"
#include "Core/Level.hh"
#include "Core/Map.hh"
#include "Core/Clock.hh"

class	Save
{
//	friend class	Position<>;
//	friend class	BonusItem;

public:
	Save();
	~Save();

private:
	Config			saveCharacter(const Character*);
	Config			saveMap(const Map*);
	Config			saveBlock(const Block*);
	Config			saveClock(const Clock*);
	Config			saveBomb(const Bomb*);

public:
	void			save(const Level*, const std::string);
};

#endif // SAVE_HH
