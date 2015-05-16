/*
 * File:   IA.hh
 * Author: buchse_a
 *
 * Created on May 7, 2015, 1:01 AM
 */

#ifndef IA_HH
#define	IA_HH

#include <cstdlib>
#include <vector>
#include "Level.hpp"
#include "Character.hpp"
#include "Position.hpp"
#include "Map.hpp"

class Bomb;
class Character;
class Item;

	enum mapSymbol { EXPLOSION, BOMBE, ENEMY };
	enum Difficulty { EASY, MEDIUM, HARD };
//	template <Style style = MIXED, Difficulty difficulty = EASY>

template<Difficulty T>
class IA
{
	public:
	  	IA(Level const* level, Character const* character):
				_self(character), _lvl(level)
		{
			(void) level;
			(void) character;
		}

	  	virtual ~IA() {}

	  	void playTurn() {}
		
		inline Character::Action Move()
		{
			return Character::MOVE_RIGHT;
		}

	private:
		std::vector<std::vector<int> > _strategyMap;
	  	std::vector<std::vector<int> >	_history;
		const Character* _self;
		const Level* 	_lvl;
		void scanMap(); // Reconstitue la map pour par la suite cree une strategie
		Character::Action easyMove(); // 3 fonctions a appeller qui depende du niveau de l'IA
		Character::Action mediumMove();
		Character::Action hardMove();

		bool BombOpportunity(); // Faut-il que le joueur place une bombe ?
		bool BombDetection(); // L'IA est-elle dans une zone dangereuse ?
		Character::Action escapeBomb();
		bool isBlockFree(const Position &) const;

};

template<>
inline Character::Action IA<EASY>::Move()
{
	std::cout << "EASY" << std::endl;
	return Character::MOVE_RIGHT;
}

template<>
inline Character::Action IA<MEDIUM>::Move()
{
	std::cout << "MIDDLE" << std::endl;
	return Character::MOVE_RIGHT;
}

template<>
inline Character::Action IA<HARD>::Move()
{
	std::cout << "HARD" << std::endl;
	return Character::MOVE_RIGHT;
}


#endif	/* IA_HPP */
