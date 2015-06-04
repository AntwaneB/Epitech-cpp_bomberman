/*
 * File:   Monster.hh
 * Author: buchse_a
 *
 * Created on June 4, 2015, 9:25 PM
 */

#ifndef MONSTER_HH
#define	MONSTER_HH

class Monster
{
public:
	Monster(const Level * level, Position const & position);
	virtual ~Monster();

private:
	bool						_moving;
	seconds_t				_movingUntil;
	Action					_direction;
};

#endif	/* MONSTER_HH */
