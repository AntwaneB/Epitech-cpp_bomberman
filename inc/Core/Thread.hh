/*
 * File:   Thread.hpp
 * Author: buchse_a
 *
 * Created on April 10, 2015, 9:58 PM
 */

#ifndef THREAD_HPP
#define	THREAD_HPP

#include <string>
#include <stdexcept>
#include <string.h>
#include <errno.h>
#include <pthread.h>

class Thread
{
public:
	class Exception : public std::runtime_error
	{
	public:
		Exception(std::string const & s) : std::runtime_error(s), _message(s) {};
		virtual ~Exception() throw() {};
		virtual const char* what() const throw() { return (_message.c_str()); }

	protected:
		std::string _message;
	};

public:
	class Task
	{
	public:
		virtual ~Task(){};
		virtual void execute() = 0;
	};

public:
	enum Status { RUNNING, NOTSTARTED, DEAD };

public:
	Thread();
	virtual ~Thread() {};

	virtual void	runTask(Task*) = 0;
	virtual void	run(void* (*startRoutine)(void*), void* routineArg) = 0;
	virtual void*	wait(void) = 0;
	virtual void	stop(void* retValue) = 0;

	Thread::Status	getStatus(void) const;

protected:
	static void*	threadRunner(void*);

protected:
	Thread::Status	_status;
	Task*				_task;
};

class PThread : public Thread
{
public:
	PThread();
	virtual ~PThread();

	virtual void	runTask(Task*);
	virtual void	run(void* (*startRoutine)(void*), void* routineArg);
	virtual void*	wait(void);
	virtual void	stop(void* retValue);

private:
	pthread_t		_thread;
};

#endif	/* THREAD_HPP */
