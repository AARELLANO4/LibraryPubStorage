// Final Project Milestone 4 
// Date Module
// File	Date.h
// Version 2.0
// Author	Alexis Arellano
// Revision History
// -----------------------------------------------------------
// Name                        Date                 Reason
// Alexis Arellano             2019/11/15		    Preliminary Setup
/////////////////////////////////////////////////////////////////

#ifndef SDDS_MENU_H
#define SDDS_DATE_H
#include <iostream>

namespace sdds
{
	class Menu;
	const int MAX_MENU_ITEMS = 20;

	class MenuItem {
	private:
		char* m_desc;

		friend class Menu;

		MenuItem();
		MenuItem(const char* description);
		~MenuItem();
		MenuItem(const MenuItem& source) = delete;
		MenuItem& operator= (const MenuItem source) = delete;

		operator bool();
		operator const char* ();
		std::ostream& write(std::ostream& os = std::cout) const;
	};

	class Menu {
		MenuItem m_title;
		MenuItem* m_menuItems[MAX_MENU_ITEMS];
		int m_no_menuItems;

	public:
		Menu();
		Menu(const char* title);
		~Menu();

		std::ostream& writeTitle(std::ostream& os=std::cout) const;
		std::ostream& writeMenu(std::ostream& os=std::cout) const;

		Menu& operator<<(const char* is);
		unsigned int getSelection();
		int operator~();
		operator int();
		operator unsigned int();
		operator bool();
		const char* operator[] (int index)const;
	};

	std::ostream& operator<<(std::ostream& os, const Menu& description);


}
#endif