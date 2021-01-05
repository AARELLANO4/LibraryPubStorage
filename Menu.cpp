// Final Project Milestone 1 
// Date Module
// File	Menu.cpp
// Version 2.0
// Author	Alexis Arellano
// Revision History
// -----------------------------------------------------------
// Name						   Date                 Reason
// Alexis Arellano             2019/11/15           Debugging
/////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;
#include "Menu.h"

namespace sdds
{
	// --------------------------------------------------------------------------
	// ----------------------------- MENUITEM CLASS -----------------------------
	// --------------------------------------------------------------------------

	// === CONSTRUCTORS/DESTRUCTOR ===

	MenuItem::MenuItem() {
		m_desc = nullptr;
	}

	MenuItem::MenuItem(const char* description) {

		if (description == nullptr || description[0] == '\0') {
			MenuItem();
		}
		else {

			m_desc = new char[strlen(description) + 1];
			strncpy(m_desc, description, strlen(description));
			m_desc[strlen(description)] = '\0';

		}
	}

	MenuItem::~MenuItem() {
		delete[] m_desc;
	}

	// === OVERLOADS ===

	MenuItem::operator bool() {
		bool validate;
		if (m_desc != nullptr && m_desc[0] != '\0') {
			validate = true;
		}
		else {
			validate = false;
		}
		return validate;
	}

	MenuItem::operator const char* () {
		return m_desc;
	}

	ostream& MenuItem::write(ostream& os) const {
		os << m_desc << endl;
		return os;
	}

	// --------------------------------------------------------------------------
	// ------------------------------- MENU CLASS -------------------------------
	// --------------------------------------------------------------------------

	// === CONSTRUCTORS/DESTRUCTORS ===

	Menu::Menu() {
		m_title.m_desc = nullptr;

		for (int i = 0; i < MAX_MENU_ITEMS; i++) {
			m_menuItems[i] = nullptr;
		}

		m_no_menuItems = 0;
	};

	Menu::Menu(const char* title) {

		m_title.m_desc = new char[strlen(title) + 1];
		strncpy(m_title.m_desc, title, strlen(title));
		m_title.m_desc[strlen(title)] = '\0';
		

		for (int i = 0; i < MAX_MENU_ITEMS; i++) {
			m_menuItems[i] = nullptr;
		}

		m_no_menuItems = 0;
	};

	Menu::~Menu() {
		for (int i = 0; i < m_no_menuItems; i++) {
			delete m_menuItems[i];
		}
	}

	// === MEMBER FUNCTIONS ===

	ostream& Menu::writeTitle(ostream& os) const {
		if (m_title.m_desc != nullptr) {
			os << m_title.m_desc;
		}

		return os;
	}

	ostream& Menu::writeMenu(ostream& os) const {
		
		if (m_title.m_desc != nullptr) {
			os << m_title.m_desc << ":" << endl;
		}

		os.setf(ios::right);
		for (int i = 0; i < m_no_menuItems; i++) {

			os << " " << i + 1 << "- ";
			m_menuItems[i]->write();
		}
		os << " 0- Exit" << endl << "> ";

		return os;
	}

	Menu& Menu::operator<<(const char* is) {
		if (m_no_menuItems < MAX_MENU_ITEMS) {
			m_no_menuItems++;
			m_menuItems[m_no_menuItems - 1] = new MenuItem(is);
		}
		return *this;
	}

	unsigned int Menu::getSelection() {
		int num;
		bool validation = false;
		writeMenu();
		do {
			cin >> num;
			if (cin.fail() || num > m_no_menuItems || num < 0) {
				cin.clear();
				cin.ignore(1000, '\n');
				validation = false;
				cout << "Invalid Selection, try again: ";
			}
			else {
				validation = true;
				cin.ignore(1000, '\n');
			}
		} while (!validation);

		return num;
	}

	int Menu::operator~() {
		return getSelection();
	}

	Menu::operator int() {
		return m_no_menuItems;
	}

	Menu::operator unsigned int() {
		return m_no_menuItems;
	}

	Menu::operator bool() {
		bool validate = false;

		if (m_menuItems[0] != nullptr) {
			validate = true;
		}

		return validate;
	}

	const char* Menu::operator[] (int index) const {

		char* menuItem;
		while (index > m_no_menuItems) {
			index = index - m_no_menuItems;
		}
		menuItem = m_menuItems[index]->m_desc;
		return menuItem;
	}

	// === OUTPUT ===
	ostream& operator<<(ostream& os, const Menu& menu) {
		menu.writeTitle(os);
		return os;
	}
}
