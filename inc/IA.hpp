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
	enum Difficulty { EASY, MEDIUM, HIGH };
//	template <Style style = MIXED, Difficulty difficulty = EASY>

template<Difficulty T>
class IA
{
	public:
	  	IA(const Level* , const Character* , Difficulty);
	  	virtual ~IA();
	  	void playTurn();

	private:
		std::vector<std::vector<int> > _strategyMap;
	  	std::vector<std::vector<int> >	_history;
		const Character* _self;
		const Level* 	_lvl;
/*		const Difficulty _diff;*/
		void scanMap(); // Reconstitue la map pour par la suite cree une strategie
		Character::Action Move();
		Character::Action easyMove(); // 3 fonctions a appeller qui depende du niveau de l'IA
		Character::Action mediumMove();
		Character::Action hardMove();

		bool BombOpportunity(); // Faut-il que le joueur place une bombe ?
		bool BombDetection(); // L'IA est-elle dans une zone dangereuse ?
		Character::Action escapeBomb();
		bool isBlockFree(const Position &) const;

};

template<Difficulty T>
IA<T>::IA(const Level* level, const Character* character, Difficulty diff):
		_lvl(level), _self(character)
{
	(void) level;
	(void) character;
	(void) diff;
}

template<Difficulty T>
IA<T>::~IA()
{

}



#endif	/* IA_HPP */
