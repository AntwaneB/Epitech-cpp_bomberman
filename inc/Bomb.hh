/*
 * File:   Bomb.hh
 * Author: buchse_a
 *
 * Created on May 7, 2015, 12:15 AM
 */

#ifndef BOMB_HH
#define	BOMB_HH

class Bomb;
class Character;

#include <vector>
#include "Item.hh"
#include "Position.hpp"
#include "Config.hpp"
#include "Character.hpp"

class Bomb : public EventHandler<Bomb>, public Subject, public Item
{
public:
	Bomb(Position const &, size_t, double, const Character*);
	virtual ~Bomb();

	void	setHitbox(std::vector<Position> const &);
	bool	hasHit(Position const &) const;

	size_t	range() const;

	void		toConfig(Config &) const;

private:
	virtual void tick(Subject*);

private:
	Config				_attributes;
	size_t				_range;
	double				_duration;
	const Character*	_owner;

	std::vector<Position>	_hitbox;
	char							_progress;
};

#endif	/* BOMB_HH */
