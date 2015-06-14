#include "Core/IA.hpp"

std::vector<std::vector<IA::Area> > objects;

IA::Area::Area(bool destructible, bool solid)
{
	_destructible = destructible;
	_wall = solid;
	_direction = Character::WAIT;
	_enemy = 0;
	_history = 0;
	_explosion = false;
	_bomb = false;
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

void IA::Area::setDestructible(bool value)
{
	_destructible = value;
}

void IA::Area::setWall(bool value)
{
	_wall = value;
}

void IA::Area::reset()
{
	_direction = Character::WAIT;
	_bomb = false;
	_enemy = 0;
	_explosion = false;
}

namespace IA
{
	template<>
	IA<EASY>::IA(Level const* level, Character* character):
			_level(level)
	{
		_self = character;
		_xCentered = false;
		_yCentered = false;
		scanMap();
		objects = _strategyMap;
	    _L = luaL_newstate();
	    luaL_openlibs(_L);

	    Lua lua;
	    lua_pushcfunction(_L, lua.luaGetObjects);
	    lua_setglobal(_L, "getObjects");

	    lua.registerObject(_L);

	    int erred = luaL_dofile(_L, "scripts/easy.lua");
	    if(erred)
	    	throw ScriptingException(luaL_checkstring(_L, -1));
	}
}

namespace IA
{
	template<>
	Character::Action IA<EASY>::Move()
	{
		static Character::Action move = Character::WAIT;

		refreshPosition();
		scanMap();
		objects = _strategyMap;
		lua_getglobal(_L, "move");
		lua_pushnumber(_L, _level->map().width());
		lua_pushnumber(_L, _level->map().height());
		lua_pushnumber(_L, _myX);
		lua_pushnumber(_L, _myY);
		lua_pushnumber(_L, move);
		lua_pcall(_L, 5, 1, 0);
		move = static_cast<Character::Action>(lua_tonumber(_L, -1));
		lua_pop(_L, 1);
		switch (move)
		{
			case Character::MOVE_UP :
				break;
			case Character::MOVE_DOWN :
				break;
			case Character::MOVE_LEFT :
				break;
			case Character::MOVE_RIGHT :
				break;
			case Character::WAIT :
				break;
			case Character::DROP_BOMB :
				break;
			default :
				throw ScriptingException("Script invalid return value is not a move");
		}
		if (move != Character::WAIT && move != Character::DROP_BOMB && _yCentered && _xCentered)
		{
			_strategyMap[_myY][_myX].incHistory();
		}
		return move;
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
        int                             i = 0;
        int                             freePath = 0;
        int 							destructibleDirections = 0;

        if (VERBOSE)
        {
        	std::cout << "running MOVE(MEDIUM) with lastAction:";
        	displayAction(_lastAction);
        	std::cout << std::endl;
        }
        if (_lastAction == Character::WAIT || (_xCentered == true && _yCentered == true))
        {
        	if (VERBOSE)
        		std::cout << " move: processing..." << std::endl;
	        while (i < 4)
	        {
	            if ((_myX + searchX[i]) >= 0 && (_myX + searchX[i]) < mapWidth && (_myY + searchY[i]) >= 0 && (_myY + searchY[i]) < mapHeight
	                    && _strategyMap[_myY + searchY[i]][_myX + searchX[i]].wall() == false
	                    && _strategyMap[_myY + searchY[i]][_myX + searchX[i]].destructible() == false
	                    && _strategyMap[_myY + searchY[i]][_myX + searchX[i]].bomb() == false
	                    && _strategyMap[_myY + searchY[i]][_myX + searchX[i]].explosion() == false)
	            {
	            	if (VERBOSE)
	                			std::cout << "history :" << _strategyMap[_myY + searchY[i]][_myX + searchX[i]].history() << std::endl; 
	                freePath++;
	                if (_strategyMap[_myY + searchY[i]][_myX + searchX[i]].history() < currentBestDirectionHistory)
	                {
	                		if (VERBOSE)
	                			std::cout << "history choosed:" << _strategyMap[_myY + searchY[i]][_myX + searchX[i]].history() << std::endl; 
	                        currentBestDirectionHistory = _strategyMap[_myY + searchY[i]][_myX + searchX[i]].history();
	                        currentBestAction = searchActions[i];
	                }
	            }
	            else if ((_myX + searchX[i]) >= 0 && (_myX + searchX[i]) < mapWidth && (_myY + searchY[i]) >= 0 && (_myY + searchY[i]) < mapHeight
	                    && _strategyMap[_myY + searchY[i]][_myX + searchX[i]].destructible() == true
	                    && _strategyMap[_myY + searchY[i]][_myX + searchX[i]].bomb() == false
	                    && _strategyMap[_myY + searchY[i]][_myX + searchX[i]].explosion() == false)
	            {
	            	destructibleDirections++;
	            }
	            i++;
	        }
	        if (freePath == 1 && destructibleDirections >= 1 && simulateEscape() == true)
	        {
	        	if (VERBOSE)
	        		std::cout << "MOVE(MEDIUM) END: dropping BOMB to extend path to enemy" << std::endl;
	        	return (Character::DROP_BOMB);
	        }
	        if (VERBOSE)
	        	std::cout << "MOVE(MEDIUM) END : found " << freePath << " possible direction(s)" << std::endl;
	        if (currentBestAction != Character::WAIT)
	        {
	        	_strategyMap[_myY][_myX].incHistory();
	        	if (VERBOSE)
	        		std::cout << "MOVE MEDIUM : incHistory(): now" << _strategyMap[_myY][_myX].history() << std::endl;
	        	_strategyMap[_myY][_myX].incHistory();
	        }
	        _lastAction = currentBestAction;
	        return (currentBestAction);
    	}
    	else
    	{
    		if (VERBOSE)
    			std::cout << "MOVE(MEDIUM) : continue w/ last mvt" << std::endl;
    		return (_lastAction);
    	}
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
		int                             mapHeight = _level->map().height();
		int                             mapWidth = _level->map().width();
		int                             counter = 0;

		if (VERBOSE)
		{
			std::cout << "running MOVE(HARD)" << std::endl;
			std::cout << "myPos : " << _myX << "/" << _myY << std::endl;
		}
		_strategyMap[_myY][_myX].setDirection(Character::MOVE_UP);
		for (int i = 0; i < 4; ++i)
		{
			if ((_myX + searchX[i]) >= 0 && (_myX + searchX[i]) < mapWidth && (_myY + searchY[i]) >= 0 && (_myY + searchY[i]) < mapHeight
					  && _strategyMap[_myY + searchY[i]][_myX + searchX[i]].wall() == false
					  && _strategyMap[_myY + searchY[i]][_myX + searchX[i]].destructible() == false
					  && _strategyMap[_myY + searchY[i]][_myX + searchX[i]].explosion() == false
					  && _strategyMap[_myY + searchY[i]][_myX + searchX[i]].bomb() == false
					  && _strategyMap[_myY + searchY[i]][_myX + searchX[i]].direction() == Character::WAIT)
			{
				 counter++;
				 _strategyMap[_myY + searchY[i]][_myX + searchX[i]].setDirection(searchActions[i]);
				 _searchNodes.push_back(Position<>(_myX + searchX[i], _myY + searchY[i]));
			}
		}
		if (VERBOSE)
			std::cout << "MOVE(HARD) : found " << counter << " possible FREE direction(s)" << std::endl;
		counter = 0;
		while (enemyDirectionFound == false && _level->characters().size() > 1)
		{
			enemyDirectionFound = scanMapForEnemy(finalAction);
		}
		if (finalAction == Character::WAIT)
		{
			if (VERBOSE)
				std::cout << "MOVE(HARD) : no free path to enemy found. Now looking into destructible paths..." << std::endl;
	 		_searchNodes.clear();
	 		enemyDirectionFound = false;
	 		scanMap();
	 		_strategyMap[_myY][_myX].setDirection(Character::MOVE_UP);
			for (int i = 0; i < 4; ++i)
	 		{
				if ((_myX + searchX[i]) >= 0 && (_myX + searchX[i]) < mapWidth && (_myY + searchY[i]) >= 0 && (_myY + searchY[i]) < mapHeight
					&& (_strategyMap[_myY + searchY[i]][_myX + searchX[i]].wall() == false
					|| _strategyMap[_myY + searchY[i]][_myX + searchX[i]].destructible() == true )
					&& _strategyMap[_myY + searchY[i]][_myX + searchX[i]].explosion() == false
					&& _strategyMap[_myY + searchY[i]][_myX + searchX[i]].bomb() == false
					&& _strategyMap[_myY + searchY[i]][_myX + searchX[i]].direction() == Character::WAIT)
				{
					if (_strategyMap[_myY + searchY[i]][_myX + searchX[i]].destructible() == true)
					{
						destructibleDirections.push_back(searchActions[i]);
					}
					 counter++;
					 _strategyMap[_myY + searchY[i]][_myX + searchX[i]].setDirection(searchActions[i]);
					 _searchNodes.push_back(Position<>(_myX + searchX[i], _myY + searchY[i]));
				}
	 		}
	 		if (VERBOSE)
	 			std::cout << "MOVE(HARD) : found " << counter << " possible FREE/DESTR direction(s)" << std::endl;
	 		while (enemyDirectionFound == false && _level->characters().size() > 1)
	 		{
				enemyDirectionFound = scanMapForEnemyThroughDestructible(finalAction);
			}
			if (destructibleDirections.size() > 0 && simulateEscape() == true)
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
							std::cout << "MOVE(HARD) : this destructible block next to this player must be exploded to reach enemy!" << std::endl;
							std::cout << "MOVE(HARD) now finished with DROP_BOMB (in order to access enemy)" << std::endl;
						}
						return (Character::DROP_BOMB);
					}
				it++;
				}
			}
		}
		if (VERBOSE)
		{
			std::cout << "MOVE(HARD) now finished with :";
			displayAction(finalAction);
			std::cout << std::endl;
		}
		return finalAction;
	}
}

namespace IA
{
    template<>
    bool IA<EASY>::BombDetection()
    {
		scanMap();
		objects = _strategyMap;
		lua_getglobal(_L, "BombDetection");
		lua_pushnumber(_L, _level->map().width());
		lua_pushnumber(_L, _level->map().height());
		lua_pushnumber(_L, _myX);
		lua_pushnumber(_L, _myY);
		lua_pcall(_L, 4, 1, 0);
		bool danger = lua_toboolean(_L, -1);
		lua_pop(_L, 1);
		switch (danger)
		{
			case true :
				break;
			case false :
				break;
			default :
				throw ScriptingException("Script invalid return must be boolean");
		}
		return danger;
    }
}

namespace IA
{
	template<>
	bool IA<EASY>::BombOpportunity()
	{
		scanMap();
		objects = _strategyMap;
		lua_getglobal(_L, "BombOpportunity");
		lua_pushnumber(_L, _level->map().width());
		lua_pushnumber(_L, _level->map().height());
		lua_pushnumber(_L, _myX);
		lua_pushnumber(_L, _myY);
		lua_pcall(_L, 4, 1, 0);
		bool danger = lua_toboolean(_L, -1);
		lua_pop(_L, 1);
		switch (danger)
		{
			case true :
				break;
			case false :
				break;
			default :
				throw ScriptingException("Script invalid return must be boolean");
		}
		return danger;
	}
}