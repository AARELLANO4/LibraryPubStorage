// Alexis Arellano November 28/2019

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