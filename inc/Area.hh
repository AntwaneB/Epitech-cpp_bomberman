#ifndef AREA_HH_
# define AREA_HH_

#include "Character.hpp"

class Area
{
public:
	Area(bool, bool, bool, bool);
	~Area();

	bool 	explosion() const;
	bool	bomb() const;
	int 	enemy() const;
	bool 	free() const;
	bool 	wall() const;
	bool 	destructible() const;

	void 	setDirection(Character::Action);
	void	setExplosion(bool);
	void	setBomb(bool);
	void 	incEnemy();
	void 	decEnemy();
	void 	setFree(bool);

private:
	bool	_bomb;
	int 	_enemy;
	bool	_wall;
	bool 	_destructible;
	bool	_free;
	bool	_explosion;

	Character::Action _direction;
	/* data */
};

#endif /* AREA_HH_ */