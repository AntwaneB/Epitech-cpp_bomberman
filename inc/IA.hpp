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
#include "Position.hpp"

// elements map de _strategyMap en plus de ceux de Map
# define	EXPLOSION	'@'
# define  BOMBE     'B'
# define  ENEMY     'E'

class Bomb;
class Character;
class Item;

namespace IA
{
  typedef	struct	s_enemyPos
  {
    int		x;
    int		y;
    int id;
  } enemyPos;

	enum Style { AGGRESSIVE, DEFENSIVE, MIXED };
	enum Difficulty { EASY, MEDIUM, HIGH };
  enum Action { WAIT, GO_LEFT, GO_UP, GO_RIGHT, GO_DOWN, DROP_BOMB};

	template <Style style = MIXED, Difficulty difficulty = EASY>
	class IA
	{
    std::vector<std::vector<int>> *_strategyMap;
	  std::vector<std::vector<int>>	*_history;
	  const Difficulty   _diff;
	  Action             _lastAction;
    const int          _xMapSize;
    const	int          _yMapSize;
	public:

	public:
	  IA(int xMapSize, int yMapSize, Difficulty);
		virtual ~IA();
  void playTurn(const std::vector<std::vector<int>> &, const Position &, std::queue<Action> &);

	private:
	  bool		amIExposed(const Position &) const;
	  Action	decideMovement(const Position &) const;
	  Action	findEscapeDirection(const Position &) const;
	  Action	findEnemyDirection(const Position &) const;
    void    generateStrategyMap (const std::vector<std::vector<int>> & map, const std::map<Position, std::list<Bomb*>> &, const std::map<Position, std::list<Character*>>);
	  int		  isEnemyAtRange(const Position &) const;
	  int		  isEscapeNode(int x, int y) const;
	  void		markBombs(const std::map<Position, std::list<Bomb*>> &);
    void    markEnemy (const std::map<Position, std::list<Character*>> &, const Position &);
    void    markItems(const std::map<Position, std::list<Item*>> & items);
	  Action	playDefensive(const Position &) const;
	  Action	playOffensive(const Position &) const;
	};

};


#endif	/* IA_HH */
