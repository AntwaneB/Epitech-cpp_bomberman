/*
 * File:   Menu.hpp
 * Author: buchse_a
 *
 * Created on May 5, 2015, 8:53 PM
 */

#ifndef MENU_HPP
#define	MENU_HPP

#include "Observer.hpp"
#include "Level.hpp"

class Menu : public Subject, public EventHandler<Menu>
{
public:
	Menu(const std::string &);
	virtual ~Menu();

	void											run();

	void											save(void) const;

	std::map<std::string, Graphics::Menu::Item*>	getItems(void) const;

private:
	void											moveUp(void);
	void											moveDown(void);
	void											moveLeft(void);
	void											moveRight(void);
	void											select(void);

private:
	Config											_cfg;
	std::string										_filename;
	std::map<std::string, Graphics::Menu::Item*>	_items;

};

#endif	/* MENU_HPP */
