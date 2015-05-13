/*
 * File:   Block.hh
 * Author: buchse_a
 *
 * Created on May 11, 2015, 11:27 AM
 */

#ifndef BLOCK_HH
#define	BLOCK_HH

#include "Observer.hpp"
#include "Position.hpp"

class Block : public EventHandler<Block>, public Subject
{
public:
	Block(Position const & position, std::string const & type);
	virtual ~Block();

	Position position() const;
	bool		destructible() const;
	bool		visible() const;
	bool		solid() const;

private:
	void tick(Subject* entity);
	void bombExploded(Subject* entity);

private:
	Position		_position;
	std::string	_type;
	Config		_attributes;
	int			_elapsedTime;
};

#endif	/* BLOCK_HH */
