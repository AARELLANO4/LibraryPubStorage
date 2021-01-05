// Alexis Arellano November 28/2019


#include <iostream>
#include "ReadWriteable.h"
namespace sdds
{

	std::ostream& operator<<(std::ostream& os, const ReadWriteable& readwrite) {
		readwrite.write(os);
		return os;
	};
	std::istream& operator>>(std::istream& is, ReadWriteable& readwrite) {
		readwrite.read(is);
		return is;
	}

}