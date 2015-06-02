/*
 * File:   ThreadPool.hpp
 * Author: buchse_a
 *
 * Created on April 18, 2015, 11:25 AM
 */

#ifndef THREADPOOL_HPP
#define	THREADPOOL_HPP

#include <queue>
#include <list>
#include <algorithm>
#include "Thread.hh"

template <typename T>
class ThreadPool
{
public:
	ThreadPool(size_t count);
	virtual ~ThreadPool();

	void		pushTask(Thread::Task*);
	void		runTasks(void);

	std::vector<Thread::Status>	getStatus(void) const;
	size_t								countAvailable(void) const;

private:
	std::list<Thread*>			_threads;
	std::queue<Thread::Task*>	_tasks;
};

template <typename T>
ThreadPool<T>::ThreadPool(size_t count)
{
	for (size_t i = 0; i < count; i++)
	{
		_threads.push_back(new T);
	}
}

template <typename T>
ThreadPool<T>::~ThreadPool()
{
	for (auto thread = _threads.begin(); thread != _threads.end(); ++thread)
	{
		if ((*thread)->getStatus() != Thread::DEAD)
		{
			(*thread)->stop(NULL);
		}
	}
}

template <typename T>
void
ThreadPool<T>::pushTask(Thread::Task* task)
{
	_tasks.push(task);
}

template <typename T>
void
ThreadPool<T>::runTasks()
{
	for (std::list<Thread*>::iterator thread = _threads.begin(); thread != _threads.end(); ++thread)
	{
		if (!_tasks.empty() && (*thread)->getStatus() == Thread::NOTSTARTED)
		{
			(*thread)->runTask(_tasks.front());
			_tasks.pop();
		}
		if (_tasks.empty())
			break;
	}
}

template <typename T>
std::vector<Thread::Status>
ThreadPool<T>::getStatus() const
{
	std::vector<Thread::Status> status;
	for (std::list<Thread*>::const_iterator thread = _threads.begin(); thread != _threads.end(); ++thread)
		status.push_back((*thread)->getStatus());

	return (status);
}

template <typename T>
size_t
ThreadPool<T>::countAvailable() const
{
	std::vector<Thread::Status> status = this->getStatus();

	return (std::count(status.begin(), status.end(), Thread::NOTSTARTED));
}

#endif	/* THREADPOOL_HPP */
