/*
 * File:   Input.hh
 * Author: buchse_a
 *
 * Created on May 22, 2015, 8:23 PM
 */

#ifndef KEYINPUT_HH
#define	KEYINPUT_HH

#include "Observer.hpp"

class KeyInput : public Subject
{
public:
	enum Key
	{
		PAUSE = 0,
		ESC,
		KEYS_P1_START,
		P1_UP,
		P1_DOWN,
		P1_LEFT,
		P1_RIGHT,
		P1_SPACE,
		KEYS_P1_END,
		KEYS_P2_START,
		P2_UP,
		P2_DOWN,
		P2_LEFT,
		P2_RIGHT,
		P2_SPACE,
		KEYS_P2_END,
		KEYS_GENERIC_START,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		SPACE,
		KEYS_GENERIC_END,
		last
	};

public:
	KeyInput(Key key) : _key(key) {}
	virtual ~KeyInput() {}

	Key	key() const
	{
		return (_key);
	}

	Key	genericKey() const
	{
		if (_key > KEYS_P1_START && _key < KEYS_P1_END)
			return (static_cast<Key>(_key + KEYS_GENERIC_START - KEYS_P1_START));
		else if (_key > KEYS_P2_START && _key < KEYS_P2_END)
			return (static_cast<Key>(_key + KEYS_GENERIC_START - KEYS_P2_START));
		else
			return (_key);
	}

private:
	Key	_key;
};

#endif	/* INPUT_HH */
