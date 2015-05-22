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
		P1_UP,
		P1_DOWN,
		P1_LEFT,
		P1_RIGHT,
		P1_SPACE,
		P1_ESC,
		P1_PAUSE,
		P2_UP,
		P2_DOWN,
		P2_LEFT,
		P2_RIGHT,
		P2_SPACE,
		P2_ESC,
		P2_PAUSE,
	};

public:
	KeyInput(Key key) : _key(key) {}
	virtual ~KeyInput() {}

	Key	key() const
	{
		return (_key);
	}

private:
	Key	_key;
};

#endif	/* INPUT_HH */
