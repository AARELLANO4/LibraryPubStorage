// Final Project Milestone 2 
// ReadWritable Module
// File	ReadWriteable.cpp
// Version 1.0
// Author	Alexis Arellano
// Revision History
// -----------------------------------------------------------
// Name                        Date                 Reason
// Alexis Arellano             2019/11/19		    Debugging
/////////////////////////////////////////////////////////////////


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