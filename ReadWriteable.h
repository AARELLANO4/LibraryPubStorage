// Final Project Milestone 4 
// Date Module
// File	ReadWriteable.h
// Version 1.0
// Author	Alexis Arellano
// Revision History
// -----------------------------------------------------------
// Name                        Date                 Reason
// Alexis Arellano             2019/11/19		    Debugging
/////////////////////////////////////////////////////////////////

#ifndef _SDDS_READWRITEABLE_H
#define _SDDS_READWRITEABLE_H
#include <iostream>

namespace sdds
{
	class ReadWriteable {
	public:
		virtual std::ostream& write(std::ostream& os = std::cout) const = 0;
		virtual std::istream& read(std::istream& is = std::cin) = 0;
	};

	std::ostream& operator<<(std::ostream& os, const ReadWriteable& readwrite);
	std::istream& operator>>(std::istream& is, ReadWriteable& readwrite);

}
#endif