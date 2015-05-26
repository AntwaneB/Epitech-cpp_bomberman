/*
 * File:   Clock.hpp
 * Author: buchse_a
 *
 * Created on March 23, 2015, 1:27 PM
 */

#ifndef CLOCK_HPP
#define	CLOCK_HPP

#include <time.h>
#include <chrono>
#include "Observer.hpp"

typedef long double	seconds_t;

class Clock : public Subject, public EventHandler<Clock>
{
public:
	Clock();
	virtual ~Clock();

	seconds_t	run(void);
	void			stop(void);
	long double	elapsedTime(void) const;
	void			restart(void);
	void			resetSec(void);
	seconds_t	seconds() const;
	seconds_t	deciseconds() const;
	void			togglePause();

private:
	void			pause();
	void			stopPause();

private:
	std::chrono::high_resolution_clock::time_point	_timer;
	seconds_t			_seconds;
	bool					_run;

	std::chrono::high_resolution_clock::time_point	_pausedAt;
	bool															_paused;
};

#endif	/* CLOCK_HPP */
