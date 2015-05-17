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
#include <random>
#include "Level.hpp"
#include "Character.hpp"
#include "Position.hpp"
#include "Map.hpp"
#include "Area.hh"

class Bomb;
class Character;
class Item;

enum Difficulty { EASY, MEDIUM, HARD };
//	template <Style style = MIXED, Difficulty difficulty = EASY>

template<Difficulty T>
class IA
{
	public:
	  	IA(Level const* level, Character const* character);
	  	virtual ~IA();
	  	void playTurn();
		Character::Action Move();

	private:
		bool	scanMapForEnemy(Character::Action & action);
		void	scanMap(); // Reconstitue la map pour par la suite cree une strategie
		void	MarkExplosion(const Position&);
		bool	BombOpportunity(); // Faut-il que le joueur place une bombe ?
		bool	BombDetection(); // L'IA est-elle dans une zone dangereuse ?
		void	ConvertMapBlock();
		bool	isBlockFree(const Position &) const;
		Character::Action escapeBomb();

	private:
		std::vector<std::vector<Area> > _strategyMap;
		std::vector<std::vector<int> >	_history;
		std::list<Position>             _escapeNodes;
		const Character*	_self;
		const Level*		_level;
};

template<Difficulty T>
IA<T>::IA(Level const* level, Character const* character):
		_self(character), _level(level)
{
	_history.resize(_level->map().width());
	int i = 0;
	for (std::vector<std::vector<int> >::iterator it = _history.begin(); it != _history.end(); it++)
	{
		_history[i].resize(_level->map().height());
		i++;
	}
	scanMap();
}

template<Difficulty T>
IA<T>::~IA()
{

}

template<Difficulty T>
bool    IA<T>::scanMapForEnemy(Character::Action & action)
{
	std::vector<int>	searchX = {0, 1, 0, -1};
	std::vector<int>	searchY = {-1, 0, 1, 0};
	Character::Action   currentDirection;
	int             	currentX;
	int             	currentY;
	int             	mapHeight = _level->map().height();
	int             	mapWidth = _level->map().width();
	int             	myX = _self->position().x();
	int             	myY = _self->position().y();
	int             	i = 0;

	if (_escapeNodes.size() == 0)
	{
		 std::cout << "[scanMapForEnemy()] : No possible path !" << std::endl;
		 action = Character::WAIT;
		 return (false);
	}
	else
	{
		currentX = _escapeNodes.front().x();
		currentY = _escapeNodes.front().y();
		_escapeNodes.pop_front();
		currentDirection = (_strategyMap[currentX][currentY]).direction();
		while (i < 4)
		{
			 if ((myX + searchX[i]) >= 0 && (myX + searchX[i]) < mapWidth && (myY + searchY[i]) >= 0 && (myY + searchY[i]) < mapHeight && _strategyMap[myX + searchX[i]][myY + searchY[i]].direction() == Character::WAIT)
			  {
				  if (_strategyMap[myX + searchX[i]][myY + searchY[i]].free() == true && _strategyMap[myX + searchX[i]][myY + searchY[i]].explosion() == false)
				  {
						 std::cout << "IA : nearest reacheable explosion-free node found !" << std::endl;
						 return (currentDirection);
				  }
				  else
					{
						 _strategyMap[myX + searchX[i]][myY + searchY[i]].setDirection(currentDirection);
						 _escapeNodes.push_back(Position(myX + searchX[i], myY + searchY[i]));
					}
			  }
			 i++;
		}
	}
	return (false);
}

template<Difficulty T>
void IA<T>::scanMap()
{
	std::vector<std::vector<Block*> > map = _level->map().map();
	std::vector<int> searchX = {0, 1, 0, -1, 0, 2, 0, -2};
	std::vector<int> searchY = {1, 0, -1, 0, 2, 0, -2, 0};
	int y;
	int x;
	(void) x;
	(void) y;

	y = 0;
	_strategyMap.resize(_level->map().width());
	for (std::vector<std::vector<Block*> >::iterator i = map.begin(); i != map.end(); ++i)
	{
		x = 0;
		_strategyMap[y].resize(_level->map().height());
		for (std::vector<Block*>::iterator j = i->begin(); j != i->end(); ++i)
		{
			Block *b = *j;
			_strategyMap[x][y] = Area(b->destructible(), b->visible(), b->solid(), b->blockBombs());
			if (b->blockBombs())
			{
				for (int i = 0; i < 4; ++i)
					_strategyMap[searchX[i]][searchY[i]].explosion();
			}
			x++;
		}
		y++;
	}
	y = 0;
	std::map<Position, std::list<Character*> > players = _level->characters();
	for (std::map<Position, std::list<Character*> >::iterator i = players.begin(); i != players.end(); ++i)
	{
		x = 0;
		for (std::list<Character*>::iterator j = i->second.begin(); j != i->second.end(); ++i)
		{
			Character* c = *j;
			Position posPlayer = c->position();
			_strategyMap[posPlayer.x()][posPlayer.y()].incEnemy();
			x++;
		}
		y++;
	}
}

template<>
inline Character::Action IA<EASY>::Move()
{
	std::vector<Character::Action>  searchActions = { Character::MOVE_UP, Character::MOVE_RIGHT, Character::MOVE_DOWN, Character::MOVE_LEFT};
	std::vector<Character::Action>  possibleDirections;
	std::vector<int>            	searchX = {0, 1, 0, -1};
	std::vector<int>           		searchY = {-1, 0, 1, 0};
	int             				mapHeight = _level->map().height();
	int             				mapWidth = _level->map().width();
	int             				myX = _self->position().x();
	int             				myY = _self->position().y();
	int             				i = 0;

	std::cout << "running MOVE(EASY)" << std::endl;
	while (i < 4)
	{
		if ((myX + searchX[i]) >= 0 && (myX + searchX[i]) < mapWidth && (myY + searchY[i]) >= 0 && (myY + searchY[i]) < mapHeight)
		{
			if (_strategyMap[myX + searchX[i]][myY + searchY[i]].free())
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
	std::vector<Character::Action>  searchActions = { Character::MOVE_UP, Character::MOVE_RIGHT, Character::MOVE_DOWN, Character::MOVE_LEFT};
	std::vector<int>   				searchX = {0, 1, 0, -1};
	std::vector<int>   				searchY = {-1, 0, 1, 0};
	Character::Action   			currentBestAction = Character::WAIT;
	int             				currentBestDirectionHistory = 5000;
	int             				mapHeight = _level->map().height();
	int             				mapWidth = _level->map().width();
	int             				myX = _self->position().x();
	int             				myY = _self->position().y();
	int             				i = 0;

	std::cout << "running MOVE(MEDIUM)" << std::endl;
	while (i < 4)
	{
		if ((myX + searchX[i]) >= 0 && (myX + searchX[i]) < mapWidth && (myY + searchY[i]) >= 0 && (myY + searchY[i]) < mapHeight)
		{
			if (_history[myX + searchX[i]][myY + searchY[i]] < currentBestDirectionHistory && _strategyMap[myX + searchX[i]][myY + searchY[i]].direction() == Character::WAIT)
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
	std::vector<Character::Action>  searchActions = { Character::MOVE_UP, Character::MOVE_RIGHT, Character::MOVE_DOWN, Character::MOVE_LEFT};
	std::vector<int>                                searchX = {0, 1, 0, -1};
	std::vector<int>                                searchY = {-1, 0, 1, 0};
	Character::Action                               finalAction = Character::WAIT;
	bool    enemyDirectionFound = false;
	int             myX = _self->position().x();
	int             myY = _self->position().y();
	int             mapHeight = _level->map().height();
	int             mapWidth = _level->map().width();
	int             i = 0;

	std::cout << "running MOVE(HARD)" << std::endl;
	_strategyMap[myX][myY].setDirection(Character::MOVE_UP);
	while (i < 4)
	{
		if ((myX + searchX[i]) >= 0 && (myX + searchX[i]) < mapWidth && (myY + searchY[i]) >= 0 && (myY + searchY[i]) < mapHeight && _strategyMap[myX + searchX[i]][myY + searchY[i]].free() == true)
		{
			_strategyMap[myX + searchX[i]][myY + searchY[i]].setDirection(searchActions[i]);
			_escapeNodes.push_back(Position(myX + searchX[i], myY + searchY[i]));
		}
		i++;
	}
	while (enemyDirectionFound == false && _level->characters().size() > 1)
	{
		 enemyDirectionFound = scanMapForEnemy(finalAction);
	}
	return finalAction;
}

template<Difficulty T>
inline bool IA<T>::BombOpportunity() // pose une bombe a +2 minimum de l ennemi
{
	std::vector<int>  	searchX = {0, 2, 0, -2};
	std::vector<int>  	searchY = {-2, 0, 2, 0};
	int             	myX = _self->position().x();
	int             	myY = _self->position().y();
	int             	mapHeight = _level->map().height();
	int             	mapWidth = _level->map().width();
	int             	i = 0;

	std::cout << "processing BombOpportunity()..." << std::endl;
	while (i < 8)
	{
		 if ((myX + searchX[i]) >= 0 && (myX + searchX[i]) < mapWidth && (myY + searchY[i]) >= 0 && (myY + searchY[i]) < mapHeight && _strategyMap[myX + searchX[i]][myY + searchY[i]].enemy() == true)
		 {
			  std::cout << "IA advise to DROP_BOMB!" << std::endl;
			  return (true);
		 }
	 i++;
	}
	std::cout << "IA : useless to drom bomb here" << std::endl;
	return (false);
}

template<>
inline bool IA<EASY>::BombOpportunity() // pose une bombe a +1 minimum de l ennemi
{
    std::vector<int> 	searchX = {0, 1, 0, -1, 0, 2, 0, -2};
    std::vector<int> 	searchY = {-1, 0, 1, 0, -2, 0, 2, 0};
    int             	myX = _self->position().x();
    int             	myY = _self->position().y();
    int             	mapHeight = _level->map().height();
    int             	mapWidth = _level->map().width();
    int             	i = 0;

    std::cout << "processing BombOpportunity()..." << std::endl;
    while (i < 8)
    {
        if ((myX + searchX[i]) >= 0 && (myX + searchX[i]) < mapWidth && (myY + searchY[i]) >= 0 && (myY + searchY[i]) < mapHeight && _strategyMap[myX + searchX[i]][myY + searchY[i]].enemy() == true)
        {
            std::cout << "IA advise to DROP_BOMB!" << std::endl;
            return (true);
        }
    	i++;
    }
    std::cout << "IA : useless to drom bomb here" << std::endl;
    return (false);
}

#endif	/* IA_HPP */
