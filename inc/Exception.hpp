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

class AssetException : public Exception
{
public:
	AssetException(std::string const & s) : Exception(s) {}

	virtual ~AssetException() throw() {}
};

class ArgumentsException : public Exception
{
public:
	ArgumentsException(std::string const & s) : Exception(s) {}

	virtual ~ArgumentsException() throw() {}
};

class ExitException : public Exception
{
public:
	ExitException(std::string const & s) : Exception(s) {}

	virtual ~ExitException() throw() {}
};

class ConfigException : public Exception
{
public:
	ConfigException(std::string const & s) : Exception(s) {}

	virtual ~ConfigException() throw() {}
};

class MapException : public Exception
{
public:
	MapException(const std::string &s): Exception("Map Error : " + s) {}
	virtual ~MapException() throw() {}
};

class PositionException : public Exception
{
public:
	PositionException(const std::string &s): Exception("Position Error : " + s) {}
	virtual ~PositionException() throw() {}
};

class EventException : public Exception
{
public:
	EventException(std::string const & s) : Exception(s) {}

	virtual ~EventException() throw() {}
};

class FactoryException : public Exception
{
public:
	FactoryException(std::string const & s) : Exception(s) {}

	virtual ~FactoryException() throw() {}
};

class ScriptingException : public Exception
{
public:
	ScriptingException(std::string const & s) : Exception("Scripting Error : " + s) {}

	virtual ~ScriptingException() throw() {}
};

class LoadException : public Exception
{
public:
	LoadException(std::string const & s) : Exception("Load Error : " + s) {}

	virtual ~LoadException() throw() {}
};

#endif	/* EXCEPTION_HPP */
