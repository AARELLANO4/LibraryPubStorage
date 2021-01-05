#include <iostream>
#include "Utils.h"

namespace sdds
{
	// AUTHOR: FARDAD SOLEIMANLOO - OOP244 WORKSHOP1
	int getInt(int min, int max) {
		int val;
		bool done = false;
		while (!done) {
			std::cin >> val;
			if (std::cin.fail()) {
				std::cin.clear();
				std::cout << "Invalid Shelf Number, Enter again: ";
			}
			else {
				if (val < min || val > max) {
					std::cout << "Invalid Shelf Number, Enter again: ";
				}
				else {
					done = true;
				}
			}
			std::cin.ignore(1000, '\n');
		}
		return val;
	}

	// AUTHOR: FARDAD SOLEIMANLOO - OOP244 WORKSHOP 2
	int readInt(int& val, int min, int max, const char* ErrorMess) {
		bool ok;
		char newline;
		do {
			std::cin >> val;
			newline = std::cin.get();
			if (std::cin.fail() || newline != '\n') {
				ok = false;
				std::cin.clear();
				std::cin.ignore(1000, '\n');
			}
			else {
				ok = val <= max && val >= min;
			}
		} while (!ok && std::cout << ErrorMess);

		return val;
	}

	// AUTHOR: FARDAD SOLEIMANLOO - OOP244 WORKSHOP 2
	void readStr(char* str, int len, const char* errorMessage) {
		bool ok;
		int len_1 = len + 1;
		do {
			ok = true;
			std::cin.getline(str, len_1, '\n');
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				ok = false;
			}
		} while (!ok && std::cout << errorMessage);
	}

	// AUTHOR: FARDAD SOLEIMANLOO - OOP244 WORKSHOP 2
	long long readISBN(long long& val, long long min, long long max, const char* ErrorMess)
	{
		bool ok;
		char newline;
		do {
			std::cin >> val;
			newline = std::cin.get();
			if (std::cin.fail() || newline != '\n') {
				ok = false;
				std::cin.clear();
				std::cin.ignore(1000, '\n');
			}
			else {
				ok = val <= max && val >= min;
			}
		} while (!ok && std::cout << ErrorMess);

		return val;
	}
}
