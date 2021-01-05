// Final Project Milestone 4 
// Book Module
// File	Book.h
// Version 1.0
// Author	Alexis Arellano
// Revision History
// -----------------------------------------------------------
// Name                        Date                 Reason
// Alexis Arellano             2019/28/11		    Initial function prototyping
/////////////////////////////////////////////////////////////////

#ifndef _SDDS_BOOK_H
#define _SDDS_BOOK_H
#include "PubRecord.h"
#include "ReadWriteable.h"
#include "Date.h"

namespace sdds
{
	class Book : public PubRecord {
		long long b_isbn;
		int b_memberID;
		Date b_returnDate;

	public:
		// -- constructors/destructors --
		Book();
		~Book();
		Book(const Book&);

		Book& operator=(const Book&);

		// -- member functions;

		char recID() const;

		int memberId() const;

		void checkIn();

		void checkOut();

		std::istream& read(std::istream& is = std::cin);
		std::ostream& write(std::ostream& os = std::cout) const;



	};
}


#endif // !_SDDS_BOOK_H
