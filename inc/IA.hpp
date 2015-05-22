/*
 * File:   IA.hh
 * Author: buchse_a
 *
 * Created on May 7, 2015, 1:01 AM
 */

#ifndef IA_HH
#define	IA_HH

#include <vector>
#include <random>
#include "Level.hpp"
#include "Character.hpp"
#include "Position.hpp"
#include "Map.hpp"
#include "Block.hh"

class Bomb;
class Item;

#define VERBOSE true

namespace IA
{
//	enum Difficulty { EASY, MEDIUM, HARD };

	class Area
	{
	public:
		 Area(bool, bool);
		 Area();
		 ~Area();

		 bool    explosion() const;
		 bool    bomb() const;
		 int     enemy() const;
		 int     history() const;
		 bool    wall() const;
		 bool    destructible() const;
		 Character::Action direction() const;

		 void    setDirection(Character::Action);
		 void    setExplosion(bool);
		 void    setBomb(bool);
		 void    incEnemy();
		 void    incHistory();

	private:
		 bool    _destructible;
		 bool    _wall;
		 bool    _bomb;
		 int     _enemy;
		 bool    _explosion;
		 int     _history;
		 Character::Action _direction;

		 /* data */
	};

	template<Difficulty T>
	class IA
	{
		public:
			IA(Level const* level, Character* character);
			virtual ~IA();
			void playTurn();

		private:
			bool	scanMapForEnemy(Character::Action & action);
            bool    scanMapForEnemyThroughDestructible(Character::Action &);
			void	scanMap();
			bool	BombOpportunity();
			bool	BombDetection();
			bool 	scanMapForEscape(Character::Action &);
			void 	debugStrategieMap();                        //Debug ONLY REMOVE when finished
            void    displayAction(Character::Action) const;     //Debug ONLY REMOVE when finished
            void    debugStrategieMapDirections();              //Debug ONLY REMOVE when finished
			Character::Action     Move();
			Character::Action     escapeBomb();

		private:
			std::vector<std::vector<Area> > _strategyMap;
			std::list<Position>             _escapeNodes;
			Character*						_self;
			const Level*					_level;
	};
}

template<IA::Difficulty T>
IA::IA<T>::IA(Level const* level, Character* character):
		_level(level)
{
	_self = character;
	scanMap();
}

template<IA::Difficulty T>
IA::IA<T>::~IA()
{

}

template<IA::Difficulty T>
void IA::IA<T>::debugStrategieMap()
{
	for (std::vector<std::vector<Area> >::iterator it = _strategyMap.begin(); it != _strategyMap.end(); ++it)
	{
		for (std::vector<Area>::iterator i = it->begin(); i != it->end(); ++i)
		{
			Area a = *i;
            if (a.explosion())
                std::cout << "x";
			else if (a.destructible() == false && a.wall() == false)
				std::cout << "_";
			else if (a.destructible())
				std::cout << "d";
			else if (a.wall())
				std::cout << "1";
			else if (a.enemy() > 0)
				std::cout << "e";
			else if (a.bomb())
				std::cout << "b";
		}
		std::cout << std::endl;
	}
}

template<IA::Difficulty T>
void IA::IA<T>::debugStrategieMapDirections()
{
    Character::Action currentDirection;
    int         myX = _self->position().x();
    int         myY = _self->position().y();
    int         x = 0;
    int         y = 0;

    for (std::vector<std::vector<Area> >::iterator it = _strategyMap.begin(); it != _strategyMap.end(); ++it)
    {
        y = 0;
        for (std::vector<Area>::iterator i = it->begin(); i != it->end(); ++i)
        {
            Area a = *i;
            currentDirection = a.direction();
            if (currentDirection == Character::MOVE_UP)
                std::cout << "U";
            else if (currentDirection == Character::MOVE_RIGHT)
                std::cout << "R";
            else if (currentDirection == Character::MOVE_DOWN)
                std::cout << "D";
            else if (currentDirection == Character::MOVE_LEFT)
                std::cout << "L";
            else if (currentDirection == Character::WAIT)
                std::cout << "W";
            else if (a.destructible() == false && a.wall() == false)
                std::cout << "1";
            else if (myX == x && myY == y)
                std::cout << "S";
        y++;
        }
        std::cout << std::endl;
    x++;
    }
}

template<IA::Difficulty T>
bool    IA::IA<T>::scanMapForEnemy(Character::Action & action)
{
    std::vector<int>        searchX = {0, 1, 0, -1};
    std::vector<int>        searchY = {-1, 0, 1, 0};
    Character::Action   currentDirection;
    int                     currentX;
    int                     currentY;
    int                     mapHeight = _level->map().height();
    int                     mapWidth = _level->map().width();
    int                     i = 0;

    if (VERBOSE)
        std::cout << "Starting scanMapForEnemy()" << std::endl;
    if (_escapeNodes.size() == 0)
    {
        if (VERBOSE)
            std::cout << "scanMapForEnemy() END : No possible path to enemy !" << std::endl;
        action = Character::WAIT;
        return (true);
    }
    else
    {
        currentX = _escapeNodes.front().x();
        currentY = _escapeNodes.front().y();
        _escapeNodes.pop_front();
        currentDirection = (_strategyMap[currentY][currentX]).direction();
        while (i < 4)
        {
            if ((currentX + searchX[i]) >= 0 && (currentX + searchX[i]) < mapWidth && (currentY + searchY[i]) >= 0
                && (currentY + searchY[i]) < mapHeight
                && _strategyMap[currentY + searchY[i]][currentX + searchX[i]].direction() == Character::WAIT)
                {
	            if (_strategyMap[currentY + searchY[i]][currentX + searchX[i]].wall() == false
	                    && _strategyMap[currentY + searchY[i]][currentX + searchX[i]].enemy() > 0)
                    {
                        if (VERBOSE)
                            std::cout << "scanMapForEnemy() END: direction to nearest enemy found !" << std::endl;
                        action = currentDirection;
                        return (true);
                    }
	            else if (_strategyMap[currentY + searchY[i]][currentX + searchX[i]].wall() == false
	                            && _strategyMap[currentY + searchY[i]][currentX + searchX[i]].enemy() == 0)
                    {
                        if (VERBOSE)
                        {
                            std::cout << "scanMapForEnemy() : no enemy found at " << currentX << "/" << currentY;
                            std::cout << ". extending search zone to " << currentX + searchX[i] << "/" << currentY + searchY[i] << std::endl;
                        }
                         _strategyMap[currentY + searchY[i]][currentX + searchX[i]].setDirection(currentDirection);
                         _escapeNodes.push_back(Position(currentX + searchX[i], currentY + searchY[i]));
                    }
                }
             i++;
        }
    }
    if (VERBOSE)
        std::cout << "scanMapForEnemy() END" << std::endl;
    return (false);
}

template<IA::Difficulty T>
void IA::IA<T>::scanMap()
{
	std::vector<std::vector<Block*> > map = _level->map().map();
	std::vector<int> searchX = {0, 1, 0, -1, 0, 2, 0, -2};
	std::vector<int> searchY = {1, 0, -1, 0, 2, 0, -2, 0};
	int y;
	int x;

	if (VERBOSE)
		std::cout << "Starting scanMap()" << std::endl;
	y = 0;
	_strategyMap.resize(_level->map().height());
	for (std::vector<std::vector<Block*> >::iterator i = map.begin(); i != map.end(); ++i)
	{
		x = 0;
		for (std::vector<Block*>::iterator j = i->begin(); j != i->end(); ++j)
		{
			_strategyMap[x].resize(_level->map().width());
			Block *b = *j;
			_strategyMap[y][x] = Area(b->destructible(), b->solid());
			_strategyMap[y][x].setExplosion(false);
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
			_strategyMap[posPlayer.y()][posPlayer.x()].incEnemy();
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
			Position p = (*i)->position();       //postion bombe
			_strategyMap[p.y()][p.x()].setBomb(true);
			_strategyMap[p.y()][p.x()].setExplosion(true);
			for (int i = 0; i < 8; i++)
			{
				if ((p.x() + searchX[i]) > 0 && (p.x() + searchX[i]) < static_cast<int>(_level->map().width())
					&& (p.y() + searchY[i]) > 0 && (p.y() + searchY[i]) < static_cast<int>(_level->map().height()))
				{
					_strategyMap[p.y() + searchY[i]][p.x() + searchX[i]].setExplosion(true);
				}
			}
		}
	}
    if (VERBOSE)
        std::cout << "scanMap() END" << std::endl;
}

template<IA::Difficulty T>
void IA::IA<T>::playTurn()
{
    int     myX = _self->position().x();
    int     myY = _self->position().y();

	if (VERBOSE)
		std::cout << "BEGIN IA" << std::endl;
    _strategyMap[myY][myX].incHistory();
	scanMap();
    bool isInDanger = BombDetection();
	Character::Action action;

	if (isInDanger)
		action = escapeBomb();
	else
	{
		if (BombOpportunity() && escapeBomb() != Character::WAIT)
			action = Character::DROP_BOMB;
		else
			action = Move();
	}
	_self->pushAction(action);
    if (VERBOSE)
    {
        debugStrategieMap();
        debugStrategieMapDirections();
        std::cout << "END IA" << std::endl;
    }
}

template<IA::Difficulty T>
Character::Action IA::IA<T>::escapeBomb()
{
    std::vector<Character::Action>  searchActions = { Character::MOVE_UP, Character::MOVE_RIGHT, Character::MOVE_DOWN, Character::MOVE_LEFT};
    std::vector<int>                searchX = {0, 1, 0, -1};
    std::vector<int>                searchY = {-1, 0, 1, 0};
    Character::Action               finalAction = Character::WAIT;
    bool                            escapeDirectionFound = false;
    int                             myX = _self->position().x();
    int                             myY = _self->position().y();
    int                             mapHeight = _level->map().height();
    int                             mapWidth = _level->map().width();
    int                             i = 0;
    int                             counter = 0; //debug purpose only

    if (VERBOSE)
    {
        std::cout << "Starting escapeBomb()" << std::endl;
        std::cout << "myPos : " << myX << "/" << myY << std::endl;
    }
    _strategyMap[myY][myX].setDirection(Character::MOVE_UP);
    while (i < 4)
    {
        if ((myX + searchX[i]) >= 0 && (myX + searchX[i]) < mapWidth && (myY + searchY[i]) >= 0 && (myY + searchY[i]) < mapHeight
                && _strategyMap[myY + searchY[i]][myX + searchX[i]].wall() == false
                && _strategyMap[myY + searchY[i]][myX + searchX[i]].destructible() == false
                && _strategyMap[myY + searchY[i]][myX + searchX[i]].direction() == Character::WAIT)
        {
            if (_strategyMap[myY + searchY[i]][myX + searchX[i]].explosion() == false)
            {
                if (VERBOSE)
                    std::cout << "escapeBomb() END : success" << std::endl;
                _escapeNodes.clear();
                return (searchActions[i]);
            }
            else
            {
            counter++; //Debug
            _strategyMap[myY + searchY[i]][myX + searchX[i]].setDirection(searchActions[i]);
            _escapeNodes.push_back(Position(myX + searchX[i], myY + searchY[i]));
            }
        }
        i++;
    }
    if (VERBOSE)
        std::cout << "escapeBomb() : found " << counter << " possible direction(s)" << std::endl;
    while (escapeDirectionFound == false)
    {
         escapeDirectionFound = scanMapForEscape(finalAction);
    }
    _escapeNodes.clear();
    if (VERBOSE)
        std::cout << "escapeBomb() END" << std::endl;
    return finalAction;
}

template<IA::Difficulty T>
bool    IA::IA<T>::scanMapForEscape(Character::Action & action)
{
    std::vector<int>    searchX = {0, 1, 0, -1};
    std::vector<int>    searchY = {-1, 0, 1, 0};
    Character::Action   currentDirection;
    int                 currentX;
    int                 currentY;
    int                 mapHeight = _level->map().height();
    int                 mapWidth = _level->map().width();
    int                 i = 0;

    if (VERBOSE)
        std::cout << "Starting scanMapForEscape()" << std::endl;
    if (_escapeNodes.size() == 0)
    {
        if (VERBOSE)
             std::cout << "scanMapForEscape() END: No possible escape path !" << std::endl;
        action = Character::WAIT;
        return (true);
    }
    else
    {
        currentX = _escapeNodes.front().x();
        currentY = _escapeNodes.front().y();
        _escapeNodes.pop_front();
        currentDirection = (_strategyMap[currentY][currentX]).direction();
        while (i < 4)
        {
            if ((currentX + searchX[i]) >= 0 && (currentX + searchX[i]) < mapWidth && (currentY + searchY[i]) >= 0
                && (currentY + searchY[i]) < mapHeight
                && _strategyMap[currentY + searchY[i]][currentX + searchX[i]].direction() == Character::WAIT)
                {
                if (VERBOSE)
                    std::cout << "scanMapForEscape() checking if " << currentX + searchX[i] << "/" << currentY + searchY[i] << "is explosion-free" << std::endl;

                if (_strategyMap[currentY + searchY[i]][currentX + searchX[i]].wall() == false
                    && _strategyMap[currentY + searchY[i]][currentX + searchX[i]].destructible() == false
                        && _strategyMap[currentY + searchY[i]][currentX + searchX[i]].explosion() == false)
                    {
                        if (VERBOSE)
                            std::cout << "scanMapForEscape() END : direction to nearest explosion-free node found :" ;
                        action = currentDirection;
                        displayAction(currentDirection);
                        return (true);
                    }
                else if (_strategyMap[currentY + searchY[i]][currentX + searchX[i]].wall() == false
                    && _strategyMap[currentY + searchY[i]][currentX + searchX[i]].destructible() == false
                        && _strategyMap[currentY + searchY[i]][currentX + searchX[i]].explosion() == true)
                    {
                        if (VERBOSE)
                        {
                            std::cout << "scanMapForEscape() : explosion zone at :" << currentX << "/" << currentY;
                            std::cout << ". Extending search zone to " << currentX + searchX[i] << "/" << currentY + searchY[i] << std::endl;
                        }
                        _strategyMap[currentY + searchY[i]][currentX + searchX[i]].setDirection(currentDirection);
                        _escapeNodes.push_back(Position(currentX + searchX[i], currentY + searchY[i]));
                    }
                }
             i++;
        }
    }
    if (VERBOSE)
        std::cout << "scanMapForEscape() END : No success" << std::endl;
    return (false);
}

template<IA::Difficulty T>
bool IA::IA<T>::BombDetection()
{
    Position currentPosition = _self->position();
    Area a = _strategyMap[currentPosition.y()][currentPosition.x()];

    if (a.bomb() || a.explosion())
        return true;
    else
        return false;
}

template<IA::Difficulty T>
void IA::IA<T>::displayAction(Character::Action action) const //Debug ONLY REMOVE when finished
{
   if(action == Character::MOVE_UP)
   {
    std::cout << "MOVE_UP" << std::endl;
   }
   if(action == Character::MOVE_LEFT)
   {
    std::cout << "MOVE_LEFT" << std::endl;
   }
      if(action == Character::MOVE_DOWN)
   {
    std::cout << "MOVE_DOWN" << std::endl;
   }
      if(action == Character::MOVE_LEFT)
   {
    std::cout << "MOVE_LEFT" << std::endl;
   }
   if(action == Character::WAIT)
   {
    std::cout << "WAIT" << std::endl;
   }
}

template<IA::Difficulty T>
bool IA::IA<T>::BombOpportunity()
{
std::vector<int>   searchX = {0, 1, 0, -1, 0, 2, 0, -2};
std::vector<int>   searchY = {-1, 0, 1, 0, -2, 0, 2, 0};
int                myX = _self->position().x();
int                myY = _self->position().y();
int                mapHeight = _level->map().height();
int                mapWidth = _level->map().width();
int                i = 0;

if (VERBOSE)
    std::cout << "Starting BombOpportunity()..." << std::endl;
i = 0;
while (i < 8)
{
      if ((myX + searchX[i]) >= 0 && (myX + searchX[i]) < mapWidth && (myY + searchY[i]) >= 0
            && (myY + searchY[i]) < mapHeight && _strategyMap[myY + searchY[i]][myX + searchX[i]].enemy() == true)
      {
        if (VERBOSE)
            std::cout << "BombOpportunity() END: advise to DROP_BOMB! (enemy nearby)" << std::endl;
        return (true);
      }
    i++;
}
if (VERBOSE)
    std::cout << "BombOpportunity() END: useless to drom bomb here (nobody around)" << std::endl;
return (false);
}

template<IA::Difficulty T>
bool    IA::IA<T>::scanMapForEnemyThroughDestructible(Character::Action & action)
{
    std::vector<int>        searchX = {0, 1, 0, -1};
    std::vector<int>        searchY = {-1, 0, 1, 0};
    Character::Action       currentDirection;
    int                     currentX;
    int                     currentY;
    int                     mapHeight = _level->map().height();
    int                     mapWidth = _level->map().width();
    int                     i = 0;

    if (VERBOSE)
        std::cout << "Starting scanMapForEnemyThroughDestructible()" << std::endl;
    if (_escapeNodes.size() == 0)
    {
        if (VERBOSE)
            std::cout << "scanMapForEnemyThroughDestructible() END : No possible path to enemy !" << std::endl;
        action = Character::WAIT;
        return (true);
    }
    else
    {
        currentX = _escapeNodes.front().x();
        currentY = _escapeNodes.front().y();
        _escapeNodes.pop_front();
        currentDirection = (_strategyMap[currentY][currentX]).direction();
        while (i < 4)
        {
            if ((currentX + searchX[i]) >= 0 && (currentX + searchX[i]) < mapWidth && (currentY + searchY[i]) >= 0
                && (currentY + searchY[i]) < mapHeight
                && _strategyMap[currentY + searchY[i]][currentX + searchX[i]].direction() == Character::WAIT)
                {
                if ((_strategyMap[currentY + searchY[i]][currentX + searchX[i]].wall() == false
                    || _strategyMap[currentY + searchY[i]][currentX + searchX[i]].destructible() == true)
                        && _strategyMap[currentY + searchY[i]][currentX + searchX[i]].enemy() > 0)
                    {
                        if (VERBOSE)
                        {
                            std::cout << "scanMapForEnemyThroughDestructible() END : direction to nearest enemy found :";
                            displayAction(currentDirection);
                        }
                        action = currentDirection;
                        return (true);
                    }
                else if ((_strategyMap[currentY + searchY[i]][currentX + searchX[i]].wall() == false
                     || _strategyMap[currentY + searchY[i]][currentX + searchX[i]].destructible() == true)
                                && _strategyMap[currentY + searchY[i]][currentX + searchX[i]].enemy() == 0)
                    {
                        if (VERBOSE)
                        {
                            std::cout << "scanMapForEnemyThroughDestructible() : no enemy found at " << currentX << "/" << currentY;
                            std::cout << ". Extending search zone to " << currentX + searchX[i] << "/" << currentY + searchY[i] << std::endl;
                        }
                         _strategyMap[currentY + searchY[i]][currentX + searchX[i]].setDirection(currentDirection);
                         _escapeNodes.push_back(Position(currentX + searchX[i], currentY + searchY[i]));
                    }
                }
             i++;
        }
    }
    if (VERBOSE)
        std::cout << "scanMapForEnemyThroughDestructible() END : No success" << std:: endl;
    return (false);
}

#endif	/* IA_HPP */
