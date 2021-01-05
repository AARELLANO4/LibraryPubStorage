// Final Project Milestone 3 
// PubRecord Module
// File	PubRecord.cpp
// Version 1.0
// Author	Alexis Arellano
// Revision History
// -----------------------------------------------------------
// Name                        Date                 Reason
// Alexis Arellano             2019/21/19		    Initialized all functions in .h
// ""						   2019/22/19			Need to update readShelfNo();
// ""						   2019/22/19			Update readShelfNo(), add operator==
// Alexis Arellano			   2019/26/19			Added shelfNo() & virtual fct
/////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Utils.h"
#include "PubRecord.h"
#include "ReadWriteable.h"

namespace sdds
{
	// ------------- Protected Functions ------------- 
	// Set the name of the publication class
	void PubRecord::name(const char* name) {
		if (name != nullptr) {

			// allocate memory if char* pointer is not empty
			p_name = new char[strlen(name)+1];

			// copy characters from name string to publication name p_name
			strncpy(p_name, name, strlen(name));

			// ensures null-byte at end of publication name to avoid buffer overflow
			p_name[strlen(name)] = '\0';
		}
		else {
			// if char* pointer is empty, set publication name to nullptr
			p_name = nullptr;
		}
	}

	// Return the name of the publication class
	const char* PubRecord::name() const {
		return p_name;
	}

	// Set the value of m_shelfNo member variable
	void PubRecord::shelfNo(int value) {
		
		if (value > 99 || value <= 999) {
			// makes sure value is valid for p_shelf
			p_shelfNo = value;
		}
		else {
			// set p_shelf to empty value
			p_shelfNo = 0;
		}
	}


	

	// ------------- Constructors/Destructors -------------

	PubRecord::PubRecord() {
		// sets object to safe empty state
		p_name = nullptr;
		p_shelfNo = 0;

		// set default media type to SDDS_CONSOLE if p_media is empty
		p_media = SDDS_CONSOLE;
	}

	PubRecord::~PubRecord() {
		//deallocate memory set for p_name in object
		delete[] p_name;
	}

	PubRecord::PubRecord(const PubRecord& source) {
		init(source);
	}

	PubRecord& PubRecord::operator=(const PubRecord& source) {

		// ensure that source object is not current object
		if (this != &source) {
			delete[]p_name;
			init(source);
		}
		return *this;
	}

	// Localize copy constructor and copy assignment logic
	void PubRecord::init(const PubRecord& source) {
		// shallow copy number of shelves & media type for current object 
		p_shelfNo = source.p_shelfNo;
		p_media = source.p_media;

		if (source.p_name != nullptr) {

			// proper copy name of PubRecord object using name() function
			name(source.p_name);
		}
		else {
			// if source.p_name is empty, set current object to empty
			p_name = nullptr;
		}
	}

	// ------------- MEMBER FUNCTIONS -------------

	void PubRecord::mediaType(int media) {
		
			p_media = media;
		
	}

	int PubRecord::mediaType()const {
		// returns media type for current object
		return p_media;
	}

	int PubRecord::shelfNo() const {
		// returns shelf number for current object
		return p_shelfNo;
	}

	void PubRecord::readShelfNo() {
		// reads in a 3 digit number for shelf number
		int shelfNo;

		// uses util function getInt() for fail proof input of 3 digit number
		shelfNo = getInt(99,999);

		// set current object's shelfNumber
		p_shelfNo = shelfNo;
	}

	// ------------- OVERLOADED OPERATORS -------------

	bool PubRecord::operator==(char c) {
		bool validation;

		// returns true if c is equal to return value of recID()
		if (c == recID()) {
			validation = true;

		}
		else {
			validation = false;
		}

		return validation;
	}

	bool PubRecord::operator==(const char* name) {

		bool validation;

		// compares substring name to name of the class
		const char* comparison = strstr(p_name,name);

		if (comparison == nullptr) {
			validation = false;

			// strstr returns nullptr if name is not a sub-string of p_name
		}
		else {
			validation = true;
		}

		return validation;
	}

	PubRecord::operator bool() const {
		bool validation;

		if (p_name != nullptr) {
			// if current object is not empty, return true
			validation = true;
		}
		else {
			// if current object is empty, return false
			validation = false;
		}

		return validation;
	}



} // end namespace