/*
 * File:   Block.hh
 * Author: buchse_a
 *
 * Created on May 11, 2015, 11:27 AM
 */

#ifndef BLOCK_HH
#define	BLOCK_HH

#include "Observer.hpp"
#include "Position.hh"
#include "Config.hh"

class Block : public EventHandler<Block>, public Subject
{
	friend class	Save;

public:
	Block(Position<> const & position, std::string const & type);
	Block(Config::Param);
	virtual ~Block();

	Position<>	position() const;
	bool			destructible() const;
	bool			visible() const;
	bool			solid() const;
	bool			blockBombs() const;
	std::string	texture() const;
	void			setBlockBombs(bool);
	void			setVisible(bool);

private:
	void tick(Subject* entity);
	void bombExploded(Subject* entity);

private:
	Position<>	_position;
	std::string	_type;
	Config		_attributes;
	int			_elapsedTime;

	bool			_visible;
	bool			_destructible;
	bool			_solid;
	bool			_blockBombs;
	std::string	_texture;
};

#endif	/* BLOCK_HH */
