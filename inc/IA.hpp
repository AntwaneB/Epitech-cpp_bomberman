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
#include <ctime>
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
	  	IA(Level const* level, Character const* character);
	  	virtual ~IA();
	  	void playTurn() {}
		Character::Action Move();

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

template<Difficulty T>
IA<T>::IA(Level const* level, Character const* character):
		_self(character), _lvl(level)
{
	(void) level;
	(void) character;
	scanMap();
}

template<Difficulty T>
IA<T>::~IA()
{

}

template<Difficulty T>
inline void IA<T>::scanMap()
{
	std::cout << "HARD OR MEDIUM scanMap()" << std::endl;
}

template<>
inline void IA<EASY>::scanMap() // NE PREND PAS EN COMPTE LES BOMBES
{
	std::vector<std::vector<Block*> > map = _lvl->map().map();
	std::cout << "EASY scanMap()" << std::endl;

	for (std::vector<std::vector<Block*> >::iterator it = map.begin(); it != map.end(); it++)
	{
		for (std::vector<Block*>::iterator it2 = it->begin(); it2 != it->end(); it2++)
		{
			Block *b = *it2;
			if (b->blockBombs())
			{
				b->setBlockBombs(false);
				b->setVisible(true);
			}
		}
	}
}

template<>
inline Character::Action IA<EASY>::Move()
{
	std::vector<Character::Action>	searchActions = { Character::MOVE_UP, Character::MOVE_RIGHT, Character::MOVE_DOWN, Character::MOVE_LEFT};
	std::vector<Character::Action>	possibleDirections;
	std::vector<int> 				searchX = {0, 1, 0, -1};
	std::vector<int>				searchY = {-1, 0, 1, 0};
	int		mapHeight = _lvl->map().height();
	int		mapWidth = _lvl->map().width();
	int		myX = _self->position().x();
	int		myY = _self->position().y();
	int		i = 0;

	std::cout << "running MOVE(EASY)" << std::endl;
	while (i < 4)
		{
			if ((myX + searchX[i]) >= 0 && (myX + searchX[i]) < mapWidth && (myY + searchY[i]) >= 0 && (myY + searchY[i]) < mapHeight)
			{
				possibleDirections.push_back(searchActions[i]);
			}
		i++;
		}
	std::cout << "[MOVE(EASY)] found : " << possibleDirections.size() << " possible directions" << std::endl;
	if (possibleDirections.size() != 0)
		return (possibleDirections[rand() % possibleDirections.size()]);
	else
		return (Character::WAIT);
}

template<>
inline Character::Action IA<MEDIUM>::Move()
{
	std::vector<Character::Action>	searchActions = { Character::MOVE_UP, Character::MOVE_RIGHT, Character::MOVE_DOWN, Character::MOVE_LEFT};
	std::vector<int> 				searchX = {0, 1, 0, -1};
	std::vector<int>				searchY = {-1, 0, 1, 0};
	Character::Action  				currentBestAction = Character::WAIT;
	int		currentBestDirectionHistory = 5000;
	int		mapHeight = _lvl->map().height();
	int		mapWidth = _lvl->map().width();
	int		myX = _self->position().x();
	int		myY = _self->position().y();
	int		i = 0;

	std::cout << "running MOVE(MEDIUM)" << std::endl;
	while (i < 4)
		{
			if ((myX + searchX[i]) >= 0 && (myX + searchX[i]) < mapWidth && (myY + searchY[i]) >= 0 && (myY + searchY[i]) < mapHeight)
			{
				if (_history[myX + searchX[i]][myY + searchY[i]] < currentBestDirectionHistory)
				{
					currentBestDirectionHistory = _history[myX + searchX[i]][myY + searchY[i]];
					currentBestAction = searchActions[i];
				}
			}
		i++;
		}
	return (currentBestAction);
}

template<>
inline Character::Action IA<HARD>::Move()
{
	std::cout << "HARD Move()" << std::endl;
	return Character::MOVE_RIGHT;
}
#endif	/* IA_HPP */
