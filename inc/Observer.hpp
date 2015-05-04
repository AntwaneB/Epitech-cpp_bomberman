/*
 * File:   Observer.hpp
 * Author: buchse_a
 *
 * Created on April 27, 2015, 10:10 PM
 */

#ifndef OBSERVER_HPP
#define	OBSERVER_HPP

#include <list>
#include <algorithm>
#include "IEntity.hpp"

enum Event
{

};

class Observer
{
public:
	virtual ~Observer() {};

protected:
	virtual void onNotify(IEntity const & entity, Event event) = 0;

private:
};

class Subject
{
public:
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
	void notify(IEntity const & entity, Event event)
	{
		for (std::list<Observer*>::iterator it = _observers.begin(); it != _observers.end(); ++it)
		{
			(*it)->onNotify(entity, event);
		}
	}

private:
	std::list<Observer*>	_observers;
};

#endif	/* OBSERVER_HPP */
