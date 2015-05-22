/*
 * File:   Clock.cpp
 * Author: buchse_a
 *
 * Created on March 23, 2015, 1:27 PM
 */

#include <unistd.h>
#include <iostream>
#include "global.hh"
#include "Clock.hpp"

Clock::Clock()
	: _run(false)
{
	this->restart();
	_seconds = 0;
}

Clock::~Clock()
{
}

long double
Clock::elapsedTime() const
{
	std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
	return (std::chrono::duration_cast<std::chrono::microseconds>(now - _timer).count());
}

void
Clock::restart()
{
	_timer = std::chrono::high_resolution_clock::now();
}

seconds_t
Clock::run(void)
{
	_run = true;

	while (_run)
	{
		this->notify(this, CLOCK_TICK);

		_seconds += elapsedTime() / 1000000;
		this->restart();
		usleep(1000000 / FPS);
	}

	return (_seconds);
}

seconds_t
Clock::seconds() const
{
	return (_seconds);
}

seconds_t
Clock::deciseconds() const
{
	return (_seconds * 10);
}

void
Clock::resetSec(void)
{
	_seconds = 0;
}

void
Clock::stop()
{
	_run = false;
}
