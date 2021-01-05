// Alexis Arellano November 28/2019

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include "PubRecord.h"
#include "Utils.h"
#include "ReadWriteable.h"
#include "Book.h"

namespace sdds
{
	// ------------- Constructors/Destructors ------------- 

	// Default Constructor
	Book::Book() : PubRecord(), b_returnDate() {
		b_isbn = 0; // set empty ISBN state to 0;
		b_memberID = 0; // set empty memberID to 0;

	}

	// Destructor
	Book::~Book() {
		// no deallocation needed in Book class, inherits deallocation on PubRecord Class
	}

	// Copy Constructor
	Book::Book(const Book& source) : PubRecord(source){

		// ^ inherit PubRecord data members from PubRecord(source)

		// shallow copy ISBN
		b_isbn = source.b_isbn;

		// set memberID to zero, copy return date
		b_memberID = 0;
		b_returnDate = source.b_returnDate;

		
	}

	// Copy Assignment Operator
	Book& Book::operator=(const Book& source) {

		// ensure that source object is not the current object
		if (this != &source) {

			// copy ISBN, return Date (using Date override operator=) and PubRecord data members (using operator= override)
			b_isbn = source.b_isbn;
			b_returnDate = source.b_returnDate;
			PubRecord::operator=(source);

			b_memberID = 0;
		}

		return *this;
	}

	// Returns 'B' to tag Book records in the file (i.e. write(is) fct)
	char Book::recID() const {
		char rec_ID;
		rec_ID = 'B';

		return rec_ID;
	}

	// Returns memberId 

	int Book::memberId() const {
		return b_memberID;
	}

	// Checks in book
	void Book::checkIn() {
		// set member ID to zero
		b_memberID = 0;

		// prints Book on the console, followed by

		write() << " checked in!" << std::endl;
	}

	// Check out book
	void Book::checkOut() {

		int tempMemID;		// temporary member id for validation
		bool validation = false;	// validation flag

		Date today; // compares b_returnDate to today. default constructor sets today's date as default

		std::cout << "Enter member ID: ";

		// when readInt successful, set it tempMemID to b_memberID
		b_memberID = readInt(tempMemID, 10000, 99999, "Invalid Member ID, Enter again: ");
		
		std::cout << "Enter return date: ";
		do {
			std::cin >> b_returnDate; // user operator>> overload to get date input
			if (b_returnDate.errCode() != 0) {
				// if errorCode is not NO_ERROR, print Error Message (ie. Bad Year, Bad Month etc)
				std::cout << b_returnDate.dateStatus() << std::endl;
			}
			else {
				// use operator overload < to compare dates 
				if (b_returnDate < today) {
					std::cout << "Please enter a future date.";
				}
				// use operator overload - to check number of days between due date and todays date
				else if ((b_returnDate - today) > 30) {
					std::cout << "The return date must be earlier than 30 days away from today.";
				}
				else {
					validation = true;
				}
			}

		} while (validation == false);

	}

	std::istream& Book::read(std::istream& is) {
		
		// temporary variables for validation before storing in class
		char tempName[41];
		long long tempISBN;
		int tempShelfNo;
		Date tempDate;
		int tempYear, tempMonth, tempDay;

		if (mediaType() == SDDS_CONSOLE) {
			// set memberID to zero
			b_memberID = 0;

			// Get user values of name
			std::cout << "Book name: ";
			readStr(tempName, 41, "Book name too long, Enter again: ");

			// when readStr successful, set input value to m_volume data member /store into class
			PubRecord::name(tempName);	// use PubRecord member function name(const char *);

			// prompt user for tempISBN
			std::cout << "ISBN: ";
			b_isbn = readISBN(tempISBN, 1000000000000, 9999999999999, "Invalid ISBN, Enter again: ");

			std::cout << "Shelf Number: ";
			// Set shelfNo using readShelfNo() member function / store into class
			PubRecord::readShelfNo();
		}

		if (mediaType() == SDDS_FILE) {

			char delimiter; // for '\t' character input
			is.getline(tempName, 41, '\t'); // get input for temporary name

			// get b_isbn, tempShelfno, b_memberID from input "isbn / shelfno / memberID"
			is >> std::noskipws >> b_isbn >> delimiter >> tempShelfNo >> delimiter >> b_memberID;

			// set p_name and p_shelfNo using member functions 
			PubRecord::name(tempName);
			shelfNo(tempShelfNo);

			if (b_memberID != 0) {

				// get b_returnDate from input ( yyyy/mm/dd )
				is >> delimiter >> tempYear >> delimiter >> tempMonth >> delimiter >> tempDay >> delimiter;
				
				// set b_returnDate using 3 arg Date() constructor;
				b_returnDate = Date(tempYear, tempMonth, tempDay);
			}
			else {
				is >> delimiter;
			}
		}

		return is;

	}

	std::ostream& Book::write(std::ostream& os) const {
		
		if (mediaType() == SDDS_CONSOLE) {
			os.width(41);		// 40 spaces
			os.setf(std::ios::left);	// left justified

			// print name and isbn
			os << name();
			os << b_isbn << "  " << shelfNo();

			// if book checked out, print name, and return date
			if (b_memberID != 0) {
				os << " " << b_memberID << "   " << b_returnDate;
			}

			// unset left justified, fill space with ' '
			os.unsetf(std::ios::left);
			os.fill(' ');
		}

		if (mediaType() == SDDS_FILE) {
			os << recID();		// print recID
			os << name();		// name
			os << '\t' << b_isbn;	// isbn
			os << '\t' << shelfNo();	// shelf number
			os << '\t' << b_memberID;	// member id
			if (b_memberID != 0) {	// if checked out, print date
				os << '\t' << b_returnDate;
			}
			os << std::endl;
		}

		return os;
	}



} // end namespace