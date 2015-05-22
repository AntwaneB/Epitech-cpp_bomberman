#include "IA.hpp"

IA::Area::Area(bool destructible, bool solid)
{
	_destructible = destructible;
	_wall = solid;
	_direction = Character::WAIT;
	_enemy = 0;
	_history = 0;
}

IA::Area::Area()
{

}

IA::Area::~Area()
{

}

bool IA::Area::explosion() const
{
	return _explosion;
}

bool IA::Area::bomb() const
{
	return _bomb;
}

int IA::Area::enemy() const
{
	return _enemy;
}

int IA::Area::history() const
{
	return _history;
}

bool IA::Area::wall() const
{
	return _wall;
}

bool IA::Area::destructible() const
{
	return _destructible;
}

Character::Action IA::Area::direction() const
{
	return _direction;
}

void IA::Area::setExplosion(bool value)
{
	_explosion = value;
}

void IA::Area::setBomb(bool value)
{
	_bomb = value;
}

void IA::Area::incEnemy()
{
	_enemy += 1;
}

void IA::Area::incHistory()
{
	_history += 1;
}

void IA::Area::setDirection(Character::Action move)
{
	_direction = move;
}

namespace IA
{
    template<>
    Character::Action IA<EASY>::Move()
    {
        std::vector<Character::Action>  searchActions = { Character::MOVE_UP, Character::MOVE_RIGHT, Character::MOVE_DOWN, Character::MOVE_LEFT};
        std::vector<Character::Action>  possibleDirections;
        std::vector<int>                searchX = {0, 1, 0, -1};
        std::vector<int>                searchY = {-1, 0, 1, 0};
        int                             mapHeight = _level->map().height();
        int                             mapWidth = _level->map().width();
        int                             myX = _self->position().x();
        int                             myY = _self->position().y();
        int                             i = 0;

        if (VERBOSE)
        	std::cout << "Starting MOVE(EASY)" << std::endl;
        while (i < 4)
        {
            if ((myX + searchX[i]) >= 0 && (myX + searchX[i]) < mapWidth && (myY + searchY[i]) >= 0 && (myY + searchY[i]) < mapHeight)
            {
                if (_strategyMap[myY + searchY[i]][myX + searchX[i]].wall() == false
                	&& _strategyMap[myY + searchY[i]][myX + searchX[i]].destructible() == false)
                        possibleDirections.push_back(searchActions[i]);
            }
            i++;
        }
        if (VERBOSE)
        	std::cout << "[MOVE(EASY)] found : " << possibleDirections.size() << " possible directions" << std::endl;
        if (possibleDirections.size() != 0)
        {
        	if (VERBOSE)
        		std::cout << "MOVE(EASY) END" << std::endl;
            return (possibleDirections[rand() % possibleDirections.size()]);
        }
        else
        {
        	if (VERBOSE)
        		std::cout << "MOVE(EASY) END" << std::endl;
            return (Character::WAIT);
    	}
    }
}

namespace IA
{
    template<>
    Character::Action IA<MEDIUM>::Move() //fonction amelioree : new : pose une bombe si impasse destructible
    {
        std::vector<Character::Action>  searchActions = { Character::MOVE_UP, Character::MOVE_RIGHT, Character::MOVE_DOWN, Character::MOVE_LEFT};
        std::vector<int>                searchX = {0, 1, 0, -1};
        std::vector<int>                searchY = {-1, 0, 1, 0};
        Character::Action               currentBestAction = Character::WAIT;
        int                             currentBestDirectionHistory = 5000;
        int                             mapHeight = _level->map().height();
        int                             mapWidth = _level->map().width();
        int                             myX = _self->position().x();
        int                             myY = _self->position().y();
        int                             i = 0;
        int                             freePath = 0;
        int 							destructibleDirections = 0;

        if (VERBOSE)
        	std::cout << "running MOVE(MEDIUM)" << std::endl;
        while (i < 4)
        {
            if ((myX + searchX[i]) >= 0 && (myX + searchX[i]) < mapWidth && (myY + searchY[i]) >= 0 && (myY + searchY[i]) < mapHeight
                    && _strategyMap[myY + searchY[i]][myX + searchX[i]].wall() == false
                    && _strategyMap[myY + searchY[i]][myX + searchX[i]].destructible() == false
                    && _strategyMap[myY + searchY[i]][myX + searchX[i]].direction() == Character::WAIT)
            {
                freePath++;
                if (_strategyMap[myY + searchY[i]][myX + searchX[i]].history() < currentBestDirectionHistory)
                {
                        currentBestDirectionHistory = _strategyMap[myY + searchY[i]][myX + searchX[i]].history();
                        currentBestAction = searchActions[i];
                }
            }
            else if ((myX + searchX[i]) >= 0 && (myX + searchX[i]) < mapWidth && (myY + searchY[i]) >= 0 && (myY + searchY[i]) < mapHeight
                    && _strategyMap[myY + searchY[i]][myX + searchX[i]].destructible() == true
                    && _strategyMap[myY + searchY[i]][myX + searchX[i]].direction() == Character::WAIT)
            {
            	destructibleDirections++;
            }
            i++;
        }
        if (freePath == 1 && destructibleDirections >= 1 && escapeBomb() != Character::WAIT) //pose un bombe si cest une impasse destructible
        {
        	if (VERBOSE)
        		std::cout << "MOVE(MEDIUM) END: dropping BOMB to extend path to enemy" << std::endl;
        	return (Character::DROP_BOMB);
        }
        if (VERBOSE)
        	std::cout << "MOVE(MEDIUM) END : found " << freePath << " possible direction(s)" << std::endl;
        return (currentBestAction);
    }
}

namespace IA
{
	template<>
	Character::Action IA<HARD>::Move()
	{
		std::list<Character::Action>::iterator	it;
		std::list<Character::Action>	destructibleDirections;
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

		if (VERBOSE)
		{
			std::cout << "running MOVE(HARD)" << std::endl;
			std::cout << "myPos : " << myX << "/" << myY << std::endl;
		}
		_strategyMap[myY][myX].setDirection(Character::MOVE_UP);
		while (i < 4)
		{
			if ((myX + searchX[i]) >= 0 && (myX + searchX[i]) < mapWidth && (myY + searchY[i]) >= 0 && (myY + searchY[i]) < mapHeight
					  && _strategyMap[myY + searchY[i]][myX + searchX[i]].wall() == false
					  && _strategyMap[myY + searchY[i]][myX + searchX[i]].destructible() == false
					  && _strategyMap[myY + searchY[i]][myX + searchX[i]].explosion() == false
					  && _strategyMap[myY + searchY[i]][myX + searchX[i]].direction() == Character::WAIT)
			{
				 counter++;
				 _strategyMap[myY + searchY[i]][myX + searchX[i]].setDirection(searchActions[i]);
				 _escapeNodes.push_back(Position(myX + searchX[i], myY + searchY[i]));
			}
			i++;
		}
		if (VERBOSE)
			std::cout << "MOVE(HARD) : found " << counter << " possible FREE direction(s)" << std::endl; // debug
		counter = 0; //debug
		while (enemyDirectionFound == false && _level->characters().size() > 1)
		{
			enemyDirectionFound = scanMapForEnemy(finalAction);
		}
		if (finalAction == Character::WAIT) // si la recherche d ennemi par les paths libres est sans succes, on recherche avec les destruct.
		{
			if (VERBOSE)
				std::cout << "MOVE(HARD) : no free path to enemy found. Now looking into destructible paths..." << std::endl;
	 		_escapeNodes.clear();
	 		enemyDirectionFound = false;
	 		scanMap();
	 		i = 0;
	 		while (i < 4)
	 		{
				if ((myX + searchX[i]) >= 0 && (myX + searchX[i]) < mapWidth && (myY + searchY[i]) >= 0 && (myY + searchY[i]) < mapHeight
					&& (_strategyMap[myY + searchY[i]][myX + searchX[i]].wall() == false 
					|| _strategyMap[myY + searchY[i]][myX + searchX[i]].destructible() == true )
					&& _strategyMap[myY + searchY[i]][myX + searchX[i]].explosion() == false
					&& _strategyMap[myY + searchY[i]][myX + searchX[i]].direction() == Character::WAIT)
				{
					if (_strategyMap[myY + searchY[i]][myX + searchX[i]].destructible() == true)
					{
						destructibleDirections.push_back(searchActions[i]);
					}
					 counter++;
					 _strategyMap[myY + searchY[i]][myX + searchX[i]].setDirection(searchActions[i]);
					 _escapeNodes.push_back(Position(myX + searchX[i], myY + searchY[i]));
				}
				i++;
	 		}
	 		if (VERBOSE)
	 			std::cout << "MOVE(HARD) : found " << counter << " possible FREE/DESTR direction(s)" << std::endl; // debug
	 		while (enemyDirectionFound == false && _level->characters().size() > 1)
	 		{
				enemyDirectionFound = scanMapForEnemyThroughDestructible(finalAction);
			}
			if (destructibleDirections.size() > 0 && escapeBomb() != Character::WAIT)//verif si le prochain path est destr. et si on peut s'echapp.
			{
				if (VERBOSE)
					std::cout << "Now comparing with destructibleDirections..." << std::endl;
				it = destructibleDirections.begin();
				while (it != destructibleDirections.end())
				{
					if (finalAction == *it)
					{
						if (VERBOSE)
						{
							std::cout << "MOVE(HARD) : this destructible block next to this player must be exploded to reach enemy!*********************" << std::endl;
							std::cout << "MOVE(HARD) now finished with DROP_BOMB (in order to access enemy)" << std::endl;
						}
						return (Character::DROP_BOMB);
					}
				it++;
				}
			}
		}
		if (VERBOSE)
			std::cout << "MOVE(HARD) now finished" << std::endl;
		_escapeNodes.clear();
		return finalAction;
	}
}

namespace IA
{
    template<>
    bool IA<EASY>::BombDetection()
    {
        return (false);
    }
}


namespace IA
{
	template<>
	bool IA<EASY>::BombOpportunity() // pose une bombe a +1 minimum de l ennemi
	{
	std::vector<int>    searchX = {0, 2, 0, -2};
	std::vector<int>    searchY = {-2, 0, 2, 0};
	int                 myX = _self->position().x();
	int                 myY = _self->position().y();
	int                 mapHeight = _level->map().height();
	int                 mapWidth = _level->map().width();
	int                 i = 0;

	if (VERBOSE)
		std::cout << "Starting BombOpportunity()..." << std::endl;
	while (i < 4)
	{
	     if ((myX + searchX[i]) >= 0 && (myX + searchX[i]) < mapWidth && (myY + searchY[i]) >= 0 && (myY + searchY[i]) < mapHeight
	        && _strategyMap[myY + searchY[i]][myX + searchX[i]].enemy() == true)
	     {
	     	if (VERBOSE)
	        	std::cout << "BombOpportunity() END : advise to DROP_BOMB!" << std::endl;
	        return (true);
	     }
	 i++;
	}
	if (VERBOSE)
		std::cout << "BombOpportunity() END : useless to drom bomb here" << std::endl;
	return (false);
	}
}