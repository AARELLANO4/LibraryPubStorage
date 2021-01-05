// Alexis Arellano November 28/2019

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include "PubRecord.h"
#include "Utils.h"
#include "ReadWriteable.h"
#include "Magazine.h"

namespace sdds
{
	// ------------- Constructors/Destructors ------------- 

	// Default Constructor
	Magazine::Magazine() : PubRecord() {
		m_volume = 1;	// set empty volume state to 1 (i.e. first volume)
		m_issue = 1;	// set empty issue state to 1. (i.e. first issue)
	}

	// Destructor
	Magazine::~Magazine() {
		// no deallocation needed in Magazine class, inherits deallocation in PubRecord class
	}

	// Copy Constructor
	Magazine::Magazine(const Magazine& source) : PubRecord(source) {

		// shallow copy volume number
		m_volume = source.m_volume;

		// shallow copy issue number
		m_issue = source.m_issue;
	}

	// Copy assignment operator
	Magazine& Magazine::operator=(const Magazine& source) {

		// ensure that source object is not current object

		if (this != &source) {

			// shallow copy volume number and issue number
			m_volume = source.m_volume;
			m_issue = source.m_issue;
			PubRecord::operator=(source);
		}

		return *this;
	}

	// Returns 'M' to tag Magazine records in the file (i.e. write(is) fct)
	char Magazine::recID() const {
		char rec_ID;
		rec_ID = 'M';

		// returns character 'M'
		return rec_ID;
	}

	// Magazines cannot be checked in or out for checkin() and checkout() print default messages
	void Magazine::checkIn() {
		std::cout << "Magazines cannot be checked in or out!" << std::endl;
	}

	void Magazine::checkOut() {
		std::cout << "Magazines cannot be checked in or out!" << std::endl;
	}

	// Override pure virtual function read() from readwriteables.h

	std::istream& Magazine::read(std::istream& is) {

		// temporary variables that will be validated before data memebers are assigned
		char tempName[45];
		int tempShelfno;
		int tempVol;
		int tempIssue;

		if (mediaType() == SDDS_CONSOLE) {

			// create a tempName string to store user input magazine Name
			std::cout << "Magazine Name: ";
			readStr(tempName, 40, "Magazine name too long, Enter again: ");

			// when readStr successful, copy tempName string into p_name data member / store into class
			PubRecord::name(tempName); // use PubRecord member function name(const char *)

			// prompt user input for tempVol
			std::cout << "Volume: ";

			// when readInt successful, set input value to m_volume data member / store into class
			m_volume = readInt(tempVol, 1, 99, "Invalid Volume number, Enter again: ");

			// prompt user input for tempIssue
			std::cout << "Issue: ";

			// when readInt successful, set input value to m_issue data member / store into class
			m_issue = readInt(tempIssue, 1, 99, "Invalid Issue number, Enter again: ");

			// Set shelfNo using readShelfNo() member function / store into class
			std::cout << "Shelf Number: ";
			PubRecord::readShelfNo();

		}

		if (mediaType() == SDDS_FILE) {

			char delimiter; // for \t and \n inputs

			is.getline(tempName, 41, '\t'); // read name, set to tempName

			// read volume, issue, tempShelfno; delimiter stores \t and \n
			is >> std::noskipws >> m_volume >> delimiter >> m_issue >> delimiter >> tempShelfno >> delimiter;

			// set name to p_name
			PubRecord::name(tempName);

			// set tempShelfo to p_shelfNo
			shelfNo(tempShelfno);

		}

		return is;
	}

	// Override pure virtual function write() from readwritables.h

	std::ostream& Magazine::write(std::ostream& os) const {

		if (mediaType() == SDDS_CONSOLE) {
			os << std::setw(41);
			os.setf(std::ios::left);
			os << name() << "       ";
			os << std::setw(2);
			os.setf(std::ios::right);
			os.fill('0');
			os << m_volume << "(" << std::setw(2);
			os.fill('0');
			os << m_issue;
			os << ")" << "  ";
			os << shelfNo();
			os.fill(' ');
			os.unsetf(std::ios::right);

		}

		if (mediaType() == SDDS_FILE) {
			os << recID();
			os << name();
			os << '\t' << m_volume;
			os << '\t' << m_issue;
			os << '\t' << shelfNo() << std::endl;
		}
		return os;
	}
} // end namespace