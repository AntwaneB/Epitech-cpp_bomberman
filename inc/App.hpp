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
#include "Observer.hpp"
#include "Menu.hpp"
#include "Graphics/Display.hh"

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

private:
	int			_ac;
	char**		_av;

	Display*		_display;
};

#endif /* !APP_HPP */
