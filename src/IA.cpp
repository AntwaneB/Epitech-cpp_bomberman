
#include "IA.hpp"

IA::IA(int xSize, int ySize) : _lastAction(GO_RIGHT), _diff(EASY)
{
  this->_history = new std::vector<std::vector<int>>(xSize, std::vector<int>(ySize, 0));
}

IA::~IA() {}

IA::Action IA::playTurn(const std::vector<sd::vector<int>> & map, const Position & myPos) const
{
  int	x = myPos.getX();
  int	y = myPos.getY();
 
  if (this->_lastAction != WAIT)
    this->_history[x][y] += 1;
  if (amIExposed(map, myPos))
    return (playDefensive(map, myPos));
  else
    return (playOffensive(map, myPos));
}

bool IA::amIExposed(std::vector<std::vector<int>> cpyMap, const Position & myPos) const
{
  markBombs(cpyMap);
  if (cpyMap[myPos.getX()][myPos.getY()] == EXPLOSION)
    return (true);
  return (false);
}

Action IA::decideMovement(std::vector<std::vector<int>> cpyMap, const Position & myPos)
{
  std::vector<Action>	actionList	{GO_LEFT, GO_RIGHT, GO_DOWN, GO_UP};
  std::vector<int>	xSearch  {-1, 1, 0, 0};
  std::vector<int>	ySearch  {0, 0, 1, -1};
  int	bestPathValue = 0;
  int	x = myPos.getX();  
  int	y = myPos.getY();  
  int	mapSize = cpyMap.size();
  Action	bestDirection = WAIT;
  std::vector<Action>	possibleDirections;
  std::vector<int>	pathLog;
  int	it = 0;

  if (this->_diff != EASY)
    markBombs(cpyMap);
  else if (this->_diff == HIGH)
    return (findEnemyDirection(cpyMap, myPos));
  while (i < 4)
    {
      if (x < mapSize && y < mapSize && x >= 0 && y >= 0 && cpyMap[xSearch[i]][ySearch[i]] == 0)
	{
	  possibleDirections.push_back(actionList[i]);
	  pathLog.push_back(this->_history[xSearch[i]][ySearch[i]]);
	}     
      i++;
    }
  if (pathLog.size() == 0)
    return (WAIT);
  else if (this->_diff == MEDIUM)
    {
      i = 0;
      while (i < pathLog.size())
	{
	  if (pathLog[i] < bestPathValue)
	    {
	      bestPathValue = pathLog[i];
	      bestDirection = possibleDirections[i];
	    }
	  it++;
	}
      this->_lastAction = bestDirection;
    }
  else
    this->_lastAction = possibleDirections[std::rand() % possibleDirection.size()];

  return (this->_lastAction);
}

Action IA::findEscapeDirection(std::vector<std::vector<int>> cpyMap, const Position & myPos)
{
  std::vector<int>	dirList	{'L', 'R', 'D', 'U'};
  std::vector<int>	xSearch  {-1, 1, 0, 0};
  std::vector<int>	ySearch  {0, 0, 1, -1};
  std::vector<Action>	actionList (83, 0);
  int	x = myPos.getX();  
  int	y = myPos.getY();  
  int	i = 0;
  int	mapSize = cpyMap.size();
  int	direction = 0;
  std::vector<IA::Action>	actionList;

  actionList['U'] = GO_UP;
  actionList['R'] = GO_RIGHT;
  actionList['D'] = GO_DOWN;
  actionList['L'] = GO_LEFT;
  markBombs(cpyMap);
  while (i < 4)
    {
      if (x < mapSize && y < mapSize && x >= 0 && y >= 0 && cpyMap[x][y] == 0)
	return (actionList[i]);
      else if (x < mapSize && y < mapSize && x >= 0 && y >= 0 && cpyMap[x][y] == EXPLOSION)
	cpyMap[x][y] = dirList[i];
      i++;
    }
  y = 0;
  while (y < mapSize && direction == 0)
    {
      x = 0;
      while (x < mapSize && direction == 0)
	{
	  if (cpyMap[x][y] == 0 || cpyMap[x][y] == EXPLOSION)
	    direction = isEscapeNode(x, y, cpyMap);
	  x++;
	}
      y++;
    }
  if (direction != 0)
    return (actionList[direction]);
  else
    return (randomMvt());
}

Action	IA::findEnemyDrection(const std::vector<sd::vector<int>> & map, const Position & myPos) const
{
  //pour niveau difficile**********************methode du path le plus court
}

int	IA::isEnemyAtRange(const std::vector<sd::vector<int>> & map, const Position & myPos)
{
  std::vector<int>	xSearch  {-1, 1, 0, 0, -2, 2, 0, 0};
  std::vector<int>	ySearch  {0, 0, 1, -1, 0, 0, 2, -2};
  std::vector<bool>	dirClear (4, true);
  std::vector<bool>	enemy	(4, false);
  int	nearestEnemy = 0;
  int	x;
  int	y;
  int	i = 0;
  int	mapSize = map.size();

  while (i < 8)
    {
      x = xSearch[i];
      y = ySearch[i];
      if (x < mapSize && y < mapSize && x >= 0 && y >= 0)
	{
	  if (dirClear[i % 4] == true && map[x][y] == ENEMY)
	    {
	      enemy[i % 4] = true;
	      if (((i / 4) + 1) > nearestEnemy)
		nearestEnemy = (i / 4) + 1;
	    }
	  else if (dirClear[i % 4] == true && map[x][y] == SOLID)
	    dirClear[i % 4] = false;
	}
      i++;
    }
  return (nearestEnemy);
}

int	IA::isEscapeNode(int subjectX, int subjectY, std::vector<std::vector<int>> & cpyMap) const
{
  std::vector<int>	xSearch  {-1, 1, 0, 0};
  std::vector<int>	ySearch  {0, 0, 1, -1};
  int	mapSize = cpyMap.size();
  int	i = 0;

  while (i < 4)
    {
      x = xSearch[i];
      y = ySearch[i];
      if (x < mapSize && y < mapSize && x >= 0 && y >= 0 && cpyMap[x][y] >= 'D' && cpyMap[subjectX][subjectY] == 0)
	return (cpyMap[x][y]);
      else if (x < mapSize && y < mapSize && x >= 0 && y >= 0 && cpyMap[x][y] >= 'D' && cpyMap[subjectX][subjectY] == EXPLOSION)
	cpyMap[subjectX][subjectY] = cpyMap[x][y];
      i++;
    }
  return (0);
}

void	IA::markBombs(std::vector<std::vector<int>> & cpyMap) const
{
  int	x = 0;
  int	x_process;
  int	y = 0;
  int	y_process;
  int	mapSize = cpyMap.size();

  while (y < mapSize)
    {
      x = 0;
      while (x < mapSize)
	{
	  if (mapSize[x][y] == BOMBEE)       //bombessur map??***************************************
	    {
	      if (x - 2 < 0 || x - 1 < 0)
		x_process = 0;
	      else
		x_process = x - 2;
	      while (x_process < mapSize && x_process < x + 2)
		{
		  if (cpyMap[x_process][y] == 0)
		    cpyMap[x_process][y] = EXPLOSION;
		  x_process++;
		}
	      if (y - 2 < 0 || y - 1 < 0)
		y_process = 0;
	      else
		y_process = y - 2;
	      while (y_process < mapSize && y_process < y + 2)
		{
		  if (cpyMap[x][y_process] == 0)
		    cpyMap[x][y_process] = EXPLOSION;
		  y_process++;
		}
	    }
	  x++;
	}
      y++;
    }
}

Action	IA::playDefensive(const std::vector<std::vector<int>> & map, const Position & myPos) const
{
  return(findEscapeDirection(map, myPos));
}

Action	IA::playOffensive(const std::vector<std::vector<int>> & map, const Position & myPos) const
{
  if (isEnemyAtRange(map, myPos) >= 1)
    return (DROP_BOMB);
  return (decideMovement(map, myPos));
}
