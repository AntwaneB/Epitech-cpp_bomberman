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

#include <iostream>
#include <list>
#include <map>
#include <algorithm>
#include <exception>

enum Event
{
	OBSERVER_DELETED,
	CLOCK_TICK,

	LEVEL_GENERATED,
	LEVEL_UPDATED,
	LEVEL_BOMB_EXPLODED,
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

	BLOCK_DESTROYED,
	ITEM_DROPPED,
	ITEM_MOVED,
	ITEM_DESTROYED,
	BOMB_DROPPED,
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
	Subject()
	{
		static size_t id = 0;

		_id = ++id;
	}

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
			*it = NULL;
			//_observers.erase(it);
		}
	}

protected:
	void notify(Subject * entity, Event event)
	{
		if (event != LEVEL_UPDATED && event != CLOCK_TICK)
			std::cout << "Event happened (" << _id << ") : " << _events[event] << std::endl;

		for (std::list<Observer*>::iterator it = _observers.begin(); it != _observers.end(); ++it)
		{
			if (*it != NULL)
				(*it)->onNotify(entity, event);
		}
	}

private:
	size_t					_id;
	std::list<Observer*>	_observers;

	std::map<Event, std::string> _events =
	{
		{ OBSERVER_DELETED, "OBSERVER_DELETED" },
		{ CLOCK_TICK, "CLOCK_TICK" },

		{ LEVEL_GENERATED, "LEVEL_GENERATED" },
		{ LEVEL_UPDATED, "LEVEL_UPDATED" },
		{ LEVEL_BOMB_EXPLODED, "LEVEL_BOMB_EXPLODED" },
		{ EXIT_TRIGGERED, "EXIT_TRIGGERED" },

		{ KEY_PRESSED_P1_UP, "KEY_PRESSED_P1_UP" },
		{ KEY_PRESSED_P1_DOWN, "KEY_PRESSED_P1_DOWN" },
		{ KEY_PRESSED_P1_LEFT, "KEY_PRESSED_P1_LEFT" },
		{ KEY_PRESSED_P1_RIGHT, "KEY_PRESSED_P1_RIGHT" },
		{ KEY_PRESSED_P1_SPACE, "KEY_PRESSED_P1_SPACE" },
		{ KEY_PRESSED_P1_ESC, "KEY_PRESSED_P1_ESC" },
		{ KEY_PRESSED_P1_PAUSE, "KEY_PRESSED_P1_PAUSE" },
		{ KEY_PRESSED_P2_UP, "KEY_PRESSED_P2_UP" },
		{ KEY_PRESSED_P2_DOWN, "KEY_PRESSED_P2_DOWN" },
		{ KEY_PRESSED_P2_LEFT, "KEY_PRESSED_P2_LEFT" },
		{ KEY_PRESSED_P2_RIGHT, "KEY_PRESSED_P2_RIGHT" },
		{ KEY_PRESSED_P2_SPACE, "KEY_PRESSED_P2_SPACE" },
		{ KEY_PRESSED_P2_ESC, "KEY_PRESSED_P2_ESC" },
		{ KEY_PRESSED_P2_PAUSE, "KEY_PRESSED_P2_PAUSE" },

		{ LEVEL_STARTED, "LEVEL_STARTED" },

		{ CHARACTER_SPAWNED, "CHARACTER_SPAWNED" },
		{ CHARACTER_DIED, "CHARACTER_DIED" },
		{ CHARACTER_MOVED, "CHARACTER_MOVED" },
		{ CHARACTER_PICKUP_ITEM, "CHARACTER_PICKUP_ITEM" },

		{ BLOCK_DESTROYED, "BLOCK_DESTROYED" },
		{ ITEM_DROPPED, "ITEM_DROPPED" },
		{ ITEM_MOVED, "ITEM_MOVED" },
		{ ITEM_DESTROYED, "ITEM_DESTROYED" },
		{ BOMB_DROPPED, "BOMB_DROPPED" },
		{ BOMB_EXPLODED, "BOMB_EXPLODED" },
	};
};

template <typename T>
class EventHandler : public Observer
{
public:
	class CastException : public std::exception
	{
	public:
		CastException(std::string const & s) : _message(s) {}
		virtual ~CastException() throw() {}
		virtual const char*	what() const throw() { return (_message.c_str()); }
	protected:
		std::string	_message;
	};

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
	template <typename U>
	U safe_cast(Subject* entity)
	{
		if (dynamic_cast<U>(entity))
			return (dynamic_cast<U>(entity));
		else
			throw EventHandler::CastException("Event thrown on not-matching entity");
	}

protected:
	std::map<const Event, void (T::*)(Subject *)>	_actions;
};

#endif	/* OBSERVER_HPP */
