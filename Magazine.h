// Alexis Arellano November 28/2019

#ifndef _SDDS_MAGAZINE_H
#define _SDDS_MAGAZINE_H
#include "PubRecord.h"
#include "ReadWriteable.h"

namespace sdds
{
	class Magazine : public PubRecord {
		int m_volume; // between 1 and 99 inclusive
		int m_issue; // between 1 and 99 inclusive

	public:
		// -- constructors/destructors --
		Magazine(); // sets class to a safe empty state
		virtual ~Magazine(); // ensure no memory leak
		Magazine(const Magazine&); // copy constructor

		Magazine& operator=(const Magazine&);

		// -- member functions --

		char recID() const;

		void checkIn();
		void checkOut();

		std::istream& read(std::istream& is = std::cin);
		std::ostream& write(std::ostream& os = std::cout) const;
	};








} // end namespace

#endif