/*
 ** App.hpp
 **
 ** Made by Antoine Buchser
 ** Login   <buchse_a@epitech.eu>
 **
 ** Started on February 6, 2015, 10:53 AM Antoine Buchser
 ** Updated on February 6, 2015, 10:53 AM Antoine Buchser
 */

#ifndef APP_HPP
#define	APP_HPP

#include "global.hh"
#include "Core/Observer.hpp"
#include "Core/Menu.hh"
#include "Graphics/Display.hh"
#include "Core/Thread.hh"
#include "Core/ThreadPool.hpp"

class App : public EventHandler<App>, public Subject
{
public:
	App(int, char**);
	~App();

	int	run(void);

private:
	bool	validateArgs(void) const;

	void	exit(Subject * entity);
	void	runLevel(Subject * entity);
	void	endLevel(Subject * entity);
	void	menuStarted(Subject * entity);

private:
	int								_ac;
	std::vector<std::string>	_av;

	Graphics::Display*			_display;
};

#endif /* !APP_HPP */
