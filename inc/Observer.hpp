/*
 * File:   Observer.hpp
 * Author: buchse_a
 *
 * Created on April 27, 2015, 10:10 PM
 */

#ifndef OBSERVER_HPP
#define	OBSERVER_HPP

class Observer;
class Subject;

#include <list>
#include <map>
#include <algorithm>

enum Event
{
	OBSERVER_DELETED,
	CLOCK_TICK,

	LEVEL_GENERATED,
	LEVEL_UPDATED,
	EXIT_TRIGGERED,

	KEY_PRESSED_P1_UP,
	KEY_PRESSED_P1_DOWN,
	KEY_PRESSED_P1_LEFT,
	KEY_PRESSED_P1_RIGHT,
	KEY_PRESSED_P1_SPACE,
	KEY_PRESSED_P1_ESC,
	KEY_PRESSED_P1_PAUSE,
	KEY_PRESSED_P2_UP,
	KEY_PRESSED_P2_DOWN,
	KEY_PRESSED_P2_LEFT,
	KEY_PRESSED_P2_RIGHT,
	KEY_PRESSED_P2_SPACE,
	KEY_PRESSED_P2_ESC,
	KEY_PRESSED_P2_PAUSE,

	LEVEL_STARTED,

	CHARACTER_SPAWNED,
	CHARACTER_DIED,
	CHARACTER_MOVED,
	CHARACTER_PICKUP_ITEM,

	ITEM_DROPPED,
	ITEM_MOVED,
	BOMB_EXPLODED,
};

class Observer
{
public:
	virtual ~Observer() {}

	virtual void onNotify(Subject * entity, Event event) = 0;

private:
};

class Subject
{
public:
	virtual ~Subject()
	{
	}

	void addObserver(Observer* observer)
	{
		if (std::find(_observers.begin(), _observers.end(), observer) == _observers.end())
		{
			_observers.push_back(observer);
		}
	}

	void removeObserver(Observer* observer)
	{
		std::list<Observer*>::iterator it = std::find(_observers.begin(), _observers.end(), observer);
		if (it != _observers.end())
		{
			_observers.erase(it);
		}
	}

protected:
	void notify(Subject * entity, Event event)
	{
		for (std::list<Observer*>::iterator it = _observers.begin(); it != _observers.end(); ++it)
		{
			(*it)->onNotify(entity, event);
		}
	}

private:
	std::list<Observer*>	_observers;
};

template <typename T>
class EventHandler : public Observer
{
public:
	virtual ~EventHandler() {}

	virtual void onNotify(Subject * entity, Event event)
	{
		if (dynamic_cast<T*>(this))
		{
			auto it = _actions.find(event);

			if (it != _actions.end())
			{
				(dynamic_cast<T*>(this)->*(it->second))(entity);
			}
		}
	}

protected:
	std::map<const Event, void (T::*)(Subject *)>	_actions;
};

#endif	/* OBSERVER_HPP */
