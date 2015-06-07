/*
 * File:   Clock.cpp
 * Author: buchse_a
 *
 * Created on March 23, 2015, 1:27 PM
 */

#include <unistd.h>
#include <iostream>
#include "global.hh"
#include "Core/Clock.hh"

Clock::Clock()
	: _run(false), _paused(false)
{
	this->restart();
	_seconds = 0;
}

Clock::Clock(Config::Param cfg)
{
	std::cout << cfg << std::endl;
	_run = cfg["run"];
	_paused = cfg["paused"];
//	_seconds = cfg["seconds"];
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

void
Clock::stop()
{
	_run = false;
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

seconds_t
Clock::centiseconds() const
{
	return (_seconds * 100);
}

void
Clock::resetSec(void)
{
	_seconds = 0;
}

void
Clock::togglePause()
{
	std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();

	if (!_paused || std::chrono::duration_cast<std::chrono::microseconds>(now - _pausedAt).count() / 1000000 >= 0.5)
	{
		_paused = true;
		_pausedAt = now;

		if (_run)
			this->pause();
		else
			this->stopPause();
	}
}

void
Clock::pause()
{
	_run = false;

	while (!_run)
	{
		this->notify(this, CLOCK_PAUSE_TICK);

		usleep(1000000 / FPS);
	}

	this->restart();
}

void
Clock::stopPause()
{
	_run = true;
}