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
}

namespace IA
{
    template<>
    Character::Action IA<MEDIUM>::Move()
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
        int                             counter = 0; //debug purpose only

        std::cout << "running MOVE(MEDIUM)" << std::endl;
        while (i < 4)
        {
            if ((myX + searchX[i]) >= 0 && (myX + searchX[i]) < mapWidth && (myY + searchY[i]) >= 0 && (myY + searchY[i]) < mapHeight
                    && _strategyMap[myX + searchX[i]][myY + searchY[i]].wall() == false
                    && _strategyMap[myX + searchX[i]][myY + searchY[i]].direction() == Character::WAIT)
            {
                counter++; //debug
                if (_strategyMap[myX + searchX[i]][myY + searchY[i]].history() < currentBestDirectionHistory)
                {
                        currentBestDirectionHistory = _strategyMap[myX + searchX[i]][myY + searchY[i]].history();
                        currentBestAction = searchActions[i];
                }
            }
            i++;
        }
        std::cout << "MOVE(MEDIUM) : found " << counter << " possible direction(s)" << std::endl;
        return (currentBestAction);
    }
}

namespace IA
{
	template<>
	Character::Action IA<HARD>::Move()
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
			  if ((myX + searchX[i]) >= 0 && (myX + searchX[i]) < mapWidth && (myY + searchY[i]) >= 0
					&& (myY + searchY[i]) < mapHeight && _strategyMap[myX + searchX[i]][myY + searchY[i]].enemy() == true)
			  {
					std::cout << "IA advise to DROP_BOMB!" << std::endl;
					return (true);
			  }
			i++;
		 }
		 std::cout << "IA : useless to drom bomb here" << std::endl;
		 return (false);
	}
}