/*
 * File:   TypeException.hpp
 * Author: buchse_a
 *
 * Created on February 9, 2015, 1:12 PM
 */

#ifndef EXCEPTION_HPP
#define	EXCEPTION_HPP

#include <string>
#include <exception>

class Exception : public std::exception
{
public:
	Exception(std::string const & s)
		: _message(s)
	{

	}

	virtual ~Exception() throw() {}

	virtual const char*	what() const throw()
	{
		return (_message.c_str());
	}

protected:
	std::string	_message;
};

class ArgumentsException : public Exception
{
public:
	ArgumentsException(std::string const & s) : Exception(s) {}

	virtual ~ArgumentsException() throw() {}
};

class ConfigException : public Exception
{
public:
	ConfigException(std::string const & s) : Exception(s) {}

	virtual ~ConfigException() throw() {}
};

#endif	/* EXCEPTION_HPP */
