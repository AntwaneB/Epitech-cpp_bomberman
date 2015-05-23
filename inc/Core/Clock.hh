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
	long double	elapsedTime(void) const;
	void			restart(void);
	void			resetSec(void);
	seconds_t	seconds() const;
	seconds_t	deciseconds() const;
	void			stop();

private:
	std::chrono::high_resolution_clock::time_point	_timer;
	seconds_t			_seconds;
	bool					_run;
};

#endif	/* CLOCK_HPP */
