
#include "Character.hpp"
#include "IA.hpp"

IA::IA(int xSize, int ySize, Difficulty diff) : _lastAction(GO_RIGHT), _diff(diff), _xMapSize(xSize), _yMapSize(ySize)
{
  this->_history = new std::vector<std::vector<int>>(xSize, std::vector<int>(ySize, 0));
  this->_strategyMap = new std::vector<std::vector<int>>(xSize, std::vector<int>(ySize, 0));
}

IA::~IA() {}

void IA::playTurn(const std::vector<sd::vector<int>> & map, const Position & myPos, std::queue<Action> & squeue)// fonction appellee depuis le personnage pour prendre une decision
{
  int	x = myPos.X();
  int	y = myPos.Y();

  if (this->_lastAction != WAIT)
  {
    this->_history[x][y] += 1;
  }
  generateStrategyMap(map, bombs, characters);
  if (amIExposed(myPos))
  {
    squeue.push(playDefensive(myPos));
  }
  else
  {
    squeue.push(playOffensive(myPos));
  }
}

bool IA::amIExposed(const Position & myPos) const // indique a l'IA s'il est en zone d'explosion de bombe
{
  if (this->_strategyMap[myPos.X()][myPos.Y()] == EXPLOSION)
  {
    return (true);
  }
  return (false);
}

Action IA::decideMovement(const Position & myPos) //decide et retourne le mvt de l'IA selon la difficulte
{
  std::vector<Action>	actionList	{GO_LEFT, GO_RIGHT, GO_DOWN, GO_UP};
  std::vector<int>	xSearch  {-1, 1, 0, 0};
  std::vector<int>	ySearch  {0, 0, 1, -1};
  int	bestPathValue = 0;
  int	x = myPos.X();
  int	y = myPos.Y();
  Action	bestDirection = WAIT;
  std::vector<Action>	possibleDirections;
  std::vector<int>	pathLog;
  int	it = 0;

  if (this->_diff == HIGH)
  {
    return (findEnemyDirection(cpyMap, myPos));
  }
  while (i < 4)
  {
    if (x < this->_xMapSize && y < this->_yMapSize && x >= 0 && y >= 0 && this->_strategyMap[xSearch[i]][ySearch[i]] == 0)
    {
      possibleDirections.push_back(actionList[i]);
      pathLog.push_back(this->_history[xSearch[i]][ySearch[i]]);
    }
    i++;
  }
  if (pathLog.size() == 0)
  {
    return (WAIT);
  }
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
{
  this->_lastAction = possibleDirections[std::rand() % possibleDirection.size()];
}
return (this->_lastAction);
}

Action IA::findEscapeDirection(const Position & myPos) //indique a l'IA en zone d'explosion la direction du node safe le plus rapide a atteindre
{
  std::vector<int>	dirList	{'L', 'R', 'D', 'U'};
  std::vector<int>	xSearch  {-1, 1, 0, 0};
  std::vector<int>	ySearch  {0, 0, 1, -1};
  std::vector<Action>	actionList (83, 0);
  int	x = myPos.getX();
  int	y = myPos.getY();
  int	i = 0;
  int	direction = 0;
  std::vector<IA::Action>	actionList;

  actionList['U'] = GO_UP;
  actionList['R'] = GO_RIGHT;
  actionList['D'] = GO_DOWN;
  actionList['L'] = GO_LEFT;
  markBombs(cpyMap);
  while (i < 4)
  {
    if (x < this->_xMapSize && y < this->_yMapSize && x >= 0 && y >= 0 && this->_strategyMap[x][y] == 0)
    {
      return (actionList[i]);
    }
    else if (x < this->_xMapSize && y < this->_yMapSize && x >= 0 && y >= 0 && this->_strategyMap[x][y] == EXPLOSION)
    this->_strategyMap[x][y] = dirList[i];
    i++;
  }
  y = 0;
  while (y < this->_yMapSize && direction == 0)
  {
    x = 0;
    while (x < this->_xMapSize && direction == 0)
    {
      if (this->_strategyMap[x][y] == 0 || this->_strategyMap[x][y] == EXPLOSION)
      {
        direction = isEscapeNode(x, y);
      }
      x++;
    }
    y++;
  }
  if (direction != 0)
  {
    return (actionList[direction]);
  }
  else
  {
    return (decideMovement(myPos));
  }
}

Action	IA::findEnemyDrection(const Position & myPos) const
{
  //pour niveau difficile**********************methode du path le plus court
}

void generateStrategyMap (const std::vector<std::vector<int>> & map, const std::map<Position, std::list<Bomb*>> & bombs, const std::map<Position, std::list<Character*>> characters) //genere _strategyMap (murs, destr, ennemis, bombes, zones d'explo) sur laquelle l'IA travaille
{



  //copier ICI le contenu de la map originale dans la _strategyMap


  if (this->_diff != EASY)
  {
    markBombs(bombs);//on ajoute dans _strategyMap les zones dexplosion
  }
  markEnemy(characters);//on marque les ennemis sur _strategyMap
}

int	IA::isEnemyAtRange(const Position & myPos) const//fonction qui retourne 0 si ennemi >2 cases , sinon renvoi la distance
{
  std::vector<int>	xSearch  {-1, 1, 0, 0, -2, 2, 0, 0};
  std::vector<int>	ySearch  {0, 0, 1, -1, 0, 0, 2, -2};
  std::vector<bool>	dirClear (4, true);
  std::vector<bool>	enemy	(4, false);
  int	nearestEnemy = 0;
  int	x;
  int	y;
  int	i = 0;

  while (i < 8)
  {
    x = xSearch[i];
    y = ySearch[i];
    if (x < this->_xMapSize && y < this->_yMapSize && x >= 0 && y >= 0)
    {
      if (dirClear[i % 4] == true && this->_strategyMap[x][y] == ENEMY)
      {
        enemy[i % 4] = true;
        if (((i / 4) + 1) > nearestEnemy)
        {
          nearestEnemy = (i / 4) + 1;
        }
      }
      else if (dirClear[i % 4] == true && this->_strategyMap[x][y] == SOLID)
      dirClear[i % 4] = false;
    }
    i++;
  }
  return (nearestEnemy);
}

int	IA::isEscapeNode(int subjectX, int subjectY) const //retourne une direction si succès, sinon marque le node comme chemin
{
  std::vector<int>	xSearch  {-1, 1, 0, 0};
  std::vector<int>	ySearch  {0, 0, 1, -1};
  int	i = 0;

  while (i < 4)
  {
    x = xSearch[i];
    y = ySearch[i];
    if (x < this->_xMapSize && y < this->_yMapSize && x >= 0 && y >= 0 && this->_strategyMap[x][y] >= 'D' && this->_strategyMap[subjectX][subjectY] == 0)
    {
      return (this->_strategyMap[x][y]);
    }
    else if (x < this->_xMapSize && y < this->_yMapSize && x >= 0 && y >= 0 && this->_strategyMap[x][y] >= 'D' && this->_strategyMap[subjectX][subjectY] == EXPLOSION)
    this->_strategyMap[subjectX][subjectY] = this->_strategyMap[x][y];
    i++;
  }
  return (0);
}

void	IA::markBombs(const	std::list<Bomb*> &) // place les bombes sur _strategyMap et definit dessus egalement les zones d'explosion
{
  int	x = 0;
  int	x_process;
  int	y = 0;
  int	y_process;

  //ICI il faut placer sur _strategyMap les bombes par 'B'

  //ensuite en dessous on ajoute les cases zones dexplosion de chaque bombe
  while (y < this->_yMapSize)
  {
    x = 0;
    while (x < this->_xMapSize)
    {
      if (this->_strategyMap[x][y] == BOMBE)
      {
        if (x - 2 < 0 || x - 1 < 0)
        {
          x_process = 0;
        }
        else
        {
          x_process = x - 2;
        }
        while (x_process < this->_xMapSize && x_process < x + 2)
        {
          if (this->_strategyMap[x_process][y] == 0)
          {
            this->_strategyMap[x_process][y] = EXPLOSION;
          }
          x_process++;
        }
        if (y - 2 < 0 || y - 1 < 0)
        {
          y_process = 0;
        }
        else
        {
          y_process = y - 2;
        }
        while (y_process < this->_yMapSize && y_process < y + 2)
        {
          if (this->_strategyMap[x][y_process] == 0)
          {
            this->_strategyMap[x][y_process] = EXPLOSION;
          }
          y_process++;
        }
      }
      x++;
    }
    y++;
  }
}

void    markEnemy(const std::map<Position, std::list<Character*>> &, const Position & myPos) //marque tous les character sauf lui meme dans _strategyMap
{

//parcourir la std::map et les placer un a un sauf himself

}

void markItems(const std::map<Position, std::list<Item*>> & items) //place sur _strategyMap les items
{

// parcourir la std::map et les placer un a un

}

Action	IA::playDefensive(const Position & myPos) const //seule priorite de l'IA : sortir de la zone d'explosion
{
  return(findEscapeDirection(map, myPos));
}

Action	IA::playOffensive(const Position & myPos) const // pose une bombe ou s'approche de l'ennemi selon la difficulte
{
  if (isEnemyAtRange(map, myPos) >= 1)
  {
    return (DROP_BOMB);
  }
  return (decideMovement(map, myPos));
}
