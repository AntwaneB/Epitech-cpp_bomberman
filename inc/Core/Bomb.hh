/*
 * File:   Bomb.hh
 * Author: buchse_a
 *
 * Created on May 7, 2015, 12:15 AM
 */

#ifndef CORE_BOMB_HH
#define	CORE_BOMB_HH

#include <vector>
#include "Item.hh"
#include "Position.hh"
#include "Config.hh"
#include "Character.hh"

class Bomb : public EventHandler<Bomb>, public Subject, public Item
{
	friend class	Save;

public:
	struct Explosion
	{
		Explosion(seconds_t time, std::vector<Position<> > const & pos)
			: lastUntil(time), positions(pos)
		{
			static size_t	_id = 0;

			id = ++_id;
		};

		size_t							id;
		seconds_t						lastUntil;
		std::vector<Position<> >	positions;
	};

public:
	Bomb(Position<> const &, size_t, double, const Character*);
	Bomb(Config::Param);
	virtual ~Bomb();

	void	setHitbox(std::vector<Position<> > const &);
	bool	hasHit(Position<> const &) const;

	size_t	range() const;
	char		progress() const;
	const Character*	owner() const;

	void		toConfig(Config::Param &) const;

private:
	virtual void tick(Subject*);

private:
	Config				_attributes;
	size_t				_range;
	double				_duration;
	const Character*	_owner;

	std::vector<Position<> >	_hitbox;
	char								_progress;
};

#endif	/* BOMB_HH */
