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

	LEVEL_GENERATED,
	EXIT_TRIGGERED,

	CHARACTER_MOVED,
	CHARACTER_DIED,
	CHARACTER_PICKUP_ITEM,

	ITEM_DROPPED,
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
		notify(this, OBSERVER_DELETED);
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
class EventHandler
{
public:
	virtual ~EventHandler() {}

protected:
	std::map<const Event, void (T::*)(Subject *)>	_actions;
};

#endif	/* OBSERVER_HPP */
