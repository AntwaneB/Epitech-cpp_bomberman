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
#include "Block.hh"

class Bomb;
class Character;
class Item;

enum Difficulty { EASY, MEDIUM, HARD };
//	template <Style style = MIXED, Difficulty difficulty = EASY>

template<Difficulty T>
class IA: public Area
{
	public:
	  	IA(Level const* level, Character* character);
	  	virtual ~IA();
	  	void playTurn();
		Character::Action Move();

	private:
		bool	scanMapForEnemy(Character::Action & action);
		void	scanMap();
		void	MarkExplosion(const Position&);
		bool	BombOpportunity();
		bool	BombDetection();
		bool 	scanMapForEscape(Character::Action &);
/*		void 	debugStrategieMap();*/
		Character::Action escapeBomb();

	private:
		std::vector<std::vector<Area> > _strategyMap;
		std::vector<std::vector<int> >	_history;
		std::list<Position>             _escapeNodes;
		Character*						_self;
		const Level*					_level;
};

template<Difficulty T>
IA<T>::IA(Level const* level, Character* character):
		_level(level)
{
	_self = character;
	_history.resize(_level->map().width());
	int i = 0;
	for (std::vector<std::vector<int> >::iterator it = _history.begin(); it != _history.end(); it++)
	{
		_history[i].resize(_level->map().height());
		i++;
	}
	scanMap();
	//debugStrategieMap();
}

template<Difficulty T>
IA<T>::~IA()
{

}

/*template<Difficulty T>
void IA<T>::debugStrategieMap()
{
	for (std::vector<std::vector<Area> >::iterator it = _strategyMap.begin(); it != _strategyMap.end(); ++it)
	{
		for (std::vector<Area>::iterator i = it->begin(); i != it->end(); ++i)
		{
			Area a = *i;
			if (a.free())
				std::cout << "7";
			else if (a.destructible())
				std::cout << "d";
			else if (a.wall())
				std::cout << "1";
			else if (a.enemy())
				std::cout << "e";
			else if (a.bomb())
				std::cout << "b";
			else if (a.explosion())
				std::cout << "x";
		}
		std::cout << std::endl;
	}
}*/

template<Difficulty T>
bool    IA<T>::scanMapForEnemy(Character::Action & action)
{
    std::vector<int>        searchX = {0, 1, 0, -1};
    std::vector<int>        searchY = {-1, 0, 1, 0};
    Character::Action   currentDirection;
    int                     currentX;
    int                     currentY;
    int                     mapHeight = _level->map().height();
    int                     mapWidth = _level->map().width();
    int                     i = 0;

    if (_escapeNodes.size() == 0)
    {
         std::cout << "[scanMapForEnemy()] : No possible path to enemy !" << std::endl;
         action = Character::WAIT;
         return (true);
    }
    else
    {
        currentX = _escapeNodes.front().x();
        currentY = _escapeNodes.front().y();
        _escapeNodes.pop_front();
        currentDirection = (_strategyMap[currentX][currentY]).direction();
        while (i < 4)
        {
            if ((currentX + searchX[i]) >= 0 && (currentX + searchX[i]) < mapWidth && (currentY + searchY[i]) >= 0
                && (currentY + searchY[i]) < mapHeight
                && _strategyMap[currentX + searchX[i]][currentY + searchY[i]].direction() == Character::WAIT)
                {
	            if (_strategyMap[currentX + searchX[i]][currentY + searchY[i]].wall() == false
	                    && _strategyMap[currentX + searchX[i]][currentY + searchY[i]].enemy() > 0)
                    {
                         std::cout << "IA : direction to nearest enemy found !" << std::endl;
                         action = currentDirection;
                         return (true);
                    }
	            else if (_strategyMap[currentX + searchX[i]][currentY + searchY[i]].wall() == false
	                            && _strategyMap[currentX + searchX[i]][currentY + searchY[i]].enemy() == 0)
                    {
                        std::cout << "scanMapForEnemy() : no enemy found at " << currentX << "/" << currentY;
                        std::cout << ". extending search zone to " << currentX + searchX[i] << "/" << currentY + searchY[i] << std::endl;
                         _strategyMap[currentX + searchX[i]][currentY + searchY[i]].setDirection(currentDirection);
                         _escapeNodes.push_back(Position(currentX + searchX[i], currentY + searchY[i]));
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

	y = 0;
	_strategyMap.resize(_level->map().width());
	for (std::vector<std::vector<Block*> >::iterator i = map.begin(); i != map.end(); ++i)
	{
		x = 0;
		for (std::vector<Block*>::iterator j = i->begin(); j != i->end(); ++j)
		{
			_strategyMap[x].resize(_level->map().height());
			Block *b = *j;
			_strategyMap[x][y] = Area(b->destructible(), b->solid());
			_strategyMap[x][y].setExplosion(false);
			x++;
		}
		y++;
	}
	y = 0;
	std::map<Position, std::list<Character*> > players = _level->characters();
	for (std::map<Position, std::list<Character*> >::iterator i = players.begin(); i != players.end(); ++i)
	{
		x = 0;
		for (std::list<Character*>::iterator j = i->second.begin(); j != i->second.end(); ++j)
		{
			Character* c = *j;
			Position posPlayer = c->position();
			_strategyMap[posPlayer.x()][posPlayer.y()].incEnemy();
			x++;
		}
		y++;
	}
	std::map<Position, std::list<Bomb*> > bombs = _level->bombs();
	y = 0;
	for (std::map<Position, std::list<Bomb*> >::iterator it = bombs.begin(); it != bombs.end(); ++it)
	{
		x = 0;
		for (std::list<Bomb*>::iterator i = it->second.begin(); i != it->second.end(); ++i)
		{
			Position p = (*i)->position();
			_strategyMap[p.x()][p.y()].setBomb(true);
			_strategyMap[p.x()][p.y()].setExplosion(true);
			for (int i = 0; i < 4; i++)
			{
				if (x + searchX[i] > 0 && x + searchX[i] < _level->map().width()
					&& y + searchY[i] > 0 && y + searchY[i] < _level->map().height())
				{
					_strategyMap[x + searchX[i]][y + searchY[i]].setExplosion(true);
				}
			}
			x++;
		}
		y++;
	}
}

template<Difficulty T>
bool IA<T>::BombDetection() // BOMBS DETECTION FOR HARD AND MEDIUM 
{
	Position currentPosition = _self->position();
	Area a = _strategyMap[currentPosition.x()][currentPosition.y()];

	if (a.bomb() || a.explosion())
		return true;
	else
		return false;
}

template<Difficulty T>
void IA<T>::playTurn()
{
	scanMap();
	bool isInDanger = BombDetection();
	Character::Action action;

	if (isInDanger)
		action = escapeBomb();
	else
	{
		if (BombOpportunity())
			action = Character::DROP_BOMB;
		else
			action = Move();
	}
	_self->pushAction(action);
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

template<Difficulty T>
inline Character::Action IA<T>::escapeBomb()
{
    std::vector<Character::Action>  searchActions = { Character::MOVE_UP, Character::MOVE_RIGHT, Character::MOVE_DOWN, Character::MOVE_LEFT};
    std::vector<int>                searchX = {0, 1, 0, -1};
    std::vector<int>                searchY = {-1, 0, 1, 0};
    Character::Action               finalAction = Character::WAIT;
    bool                                                    escapeDirectionFound = false;
    int                                                     myX = _self->position().x();
    int                                                     myY = _self->position().y();
    int                                                     mapHeight = _level->map().height();
    int                                                     mapWidth = _level->map().width();
    int                                                     i = 0;
    int                                                             counter = 0; //debug purpose only

    std::cout << "running MOVE(HARD)" << std::endl;
    std::cout << "myPos : " << myX << "/" << myY << std::endl;
    _strategyMap[myX][myY].setDirection(Character::MOVE_UP);
    while (i < 4)
    {
        if ((myX + searchX[i]) >= 0 && (myX + searchX[i]) < mapWidth && (myY + searchY[i]) >= 0 && (myY + searchY[i]) < mapHeight
                && _strategyMap[myX + searchX[i]][myY + searchY[i]].wall() == false
                && _strategyMap[myX + searchX[i]][myY + searchY[i]].direction() == Character::WAIT)
        {
            counter++;
            _strategyMap[myX + searchX[i]][myY + searchY[i]].setDirection(searchActions[i]);
            _escapeNodes.push_back(Position(myX + searchX[i], myY + searchY[i]));
        }
        i++;
    }
    while (escapeDirectionFound == false)
    {
         escapeDirectionFound = scanMapForEscape(finalAction);
    }
    _escapeNodes.clear();
    return finalAction;
}

template<Difficulty T>
bool    IA<T>::scanMapForEscape(Character::Action & action)
{
    std::vector<int>        searchX = {0, 1, 0, -1};
    std::vector<int>        searchY = {-1, 0, 1, 0};
    Character::Action   currentDirection;
    int                     currentX;
    int                     currentY;
    int                     mapHeight = _level->map().height();
    int                     mapWidth = _level->map().width();
    int                     i = 0;

    if (_escapeNodes.size() == 0)
    {
             std::cout << "[scanMapForEscape()] : No possible escape path !" << std::endl;
             action = Character::WAIT;
             return (true);
    }
    else
    {
        currentX = _escapeNodes.front().x();
        currentY = _escapeNodes.front().y();
        _escapeNodes.pop_front();
        currentDirection = (_strategyMap[currentX][currentY]).direction();
        while (i < 4)
        {
            if ((currentX + searchX[i]) >= 0 && (currentX + searchX[i]) < mapWidth && (currentY + searchY[i]) >= 0
                && (currentY + searchY[i]) < mapHeight
                && _strategyMap[currentX + searchX[i]][currentY + searchY[i]].direction() == Character::WAIT)
                {
                if (_strategyMap[currentX + searchX[i]][currentY + searchY[i]].wall() == false
                        && _strategyMap[currentX + searchX[i]][currentY + searchY[i]].explosion() == false)
                    {
                        std::cout << "IA : direction to nearest explosion-free node found !" << std::endl;
                        action = currentDirection;
                        return (true);
                    }
                else if (_strategyMap[currentX + searchX[i]][currentY + searchY[i]].wall() == false
                        && _strategyMap[currentX + searchX[i]][currentY + searchY[i]].explosion() == true)
                    {
                        std::cout << "scanMapForEscape() : explosion zone at :" << currentX << "/" << currentY;
                        std::cout << ". extending search zone to " << currentX + searchX[i] << "/" << currentY + searchY[i] << std::endl;
                        _strategyMap[currentX + searchX[i]][currentY + searchY[i]].setDirection(currentDirection);
                        _escapeNodes.push_back(Position(currentX + searchX[i], currentY + searchY[i]));
                    }
                }
             i++;
        }
    }
    return (false);
}

template<>
inline bool IA<EASY>::BombDetection() // BOMBS DETECTION FOR EASY IA
{
	return (false);
}

template<>
inline Character::Action IA<EASY>::Move()
{
    std::vector<Character::Action>  searchActions = { Character::MOVE_UP, Character::MOVE_RIGHT, Character::MOVE_DOWN, Character::MOVE_LEFT};
    std::vector<Character::Action>  possibleDirections;
    std::vector<int>                searchX = {0, 1, 0, -1};
    std::vector<int>                        searchY = {-1, 0, 1, 0};
    int                                             mapHeight = _level->map().height();
    int                                             mapWidth = _level->map().width();
    int                                             myX = _self->position().x();
    int                                             myY = _self->position().y();
    int                                             i = 0;

    std::cout << "running MOVE(EASY)" << std::endl;
    while (i < 4)
    {
        if ((myX + searchX[i]) >= 0 && (myX + searchX[i]) < mapWidth && (myY + searchY[i]) >= 0 && (myY + searchY[i]) < mapHeight)
        {
            if (_strategyMap[myX + searchX[i]][myY + searchY[i]].wall() == false)
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
    std::vector<int>                                searchX = {0, 1, 0, -1};
    std::vector<int>                                searchY = {-1, 0, 1, 0};
    Character::Action                       currentBestAction = Character::WAIT;
    int                                             currentBestDirectionHistory = 5000;
    int                                             mapHeight = _level->map().height();
    int                                             mapWidth = _level->map().width();
    int                                             myX = _self->position().x();
    int                                             myY = _self->position().y();
    int                                             i = 0;
    int                                                             counter = 0; //debug purpose only

    std::cout << "running MOVE(MEDIUM)" << std::endl;
    while (i < 4)
    {
        if ((myX + searchX[i]) >= 0 && (myX + searchX[i]) < mapWidth && (myY + searchY[i]) >= 0 && (myY + searchY[i]) < mapHeight
                && _strategyMap[myX + searchX[i]][myY + searchY[i]].wall() == false
                && _strategyMap[myX + searchX[i]][myY + searchY[i]].direction() == Character::WAIT)
        {
            counter++;
            if (_history[myX + searchX[i]][myY + searchY[i]] < currentBestDirectionHistory)
            {
                    currentBestDirectionHistory = _history[myX + searchX[i]][myY + searchY[i]];
                    currentBestAction = searchActions[i];
            }
        }
        i++;
    }
    std::cout << "MOVE(MEDIUM) : found " << counter << " possible direction(s)" << std::endl;
    return (currentBestAction);
}

template<>
inline Character::Action IA<HARD>::Move()
{
    std::vector<Character::Action>  searchActions = { Character::MOVE_UP, Character::MOVE_RIGHT, Character::MOVE_DOWN, Character::MOVE_LEFT};
    std::vector<int>                searchX = {0, 1, 0, -1};
    std::vector<int>                searchY = {-1, 0, 1, 0};
    Character::Action               finalAction = Character::WAIT;
    bool                            enemyDirectionFound = false;
    int                             myX = _self->position().x();
    int                             myY = _self->position().y();
    int                             mapHeight = _level->map().height();
    int                             mapWidth = _level->map().width();
    int                             i = 0;
    int                             counter = 0;

    std::cout << "running MOVE(HARD)" << std::endl;
    std::cout << "myPos : " << myX << "/" << myY << std::endl;
    _strategyMap[myX][myY].setDirection(Character::MOVE_UP);
    while (i < 4)
    {
            if ((myX + searchX[i]) >= 0 && (myX + searchX[i]) < mapWidth && (myY + searchY[i]) >= 0 && (myY + searchY[i]) < mapHeight
                    && _strategyMap[myX + searchX[i]][myY + searchY[i]].wall() == false
                    && _strategyMap[myX + searchX[i]][myY + searchY[i]].direction() == Character::WAIT)
            {
                counter++;
                _strategyMap[myX + searchX[i]][myY + searchY[i]].setDirection(searchActions[i]);
                _escapeNodes.push_back(Position(myX + searchX[i], myY + searchY[i]));
            }
            i++;
    }
    while (enemyDirectionFound == false && _level->characters().size() > 1)
    {
         enemyDirectionFound = scanMapForEnemy(finalAction);
    }
    _escapeNodes.clear();
    return finalAction;
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
