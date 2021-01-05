// Final Project Milestone 4 
// PubRecord Module
// File	PubRecord.h
// Version 1.0
// Author	Alexis Arellano
// Revision History
// -----------------------------------------------------------
// Name                        Date                 Reason
// Alexis Arellano             2019/21/19		    Initialized prototypes
// Alexis Arellano			   2019/22/19			Added init() prototype
// Alexis Arellano			   2019/26/19			Added shelfNo() & virtual fct
/////////////////////////////////////////////////////////////////

#ifndef _SDDS_PUBRECORD_H
#define _SDDS_PUBRECORD_H
#include <iostream>
#include <cstring>
#include "ReadWriteable.h"

#define SDDS_CONSOLE 1
#define SDDS_FILE 2

namespace sdds
{
	class PubRecord : public ReadWriteable {

		// -- data members --
		char* p_name;	// name of publication
		int p_shelfNo;	// shelf number publication is held in
		int p_media;	// type of media publication is to be written

	public:
		// pure virtual function recID; returns char, does not change class
		virtual char recID() const = 0;

	protected:

		// function that receives constant char pointer to set name of publication dynamically
		void name(const char* name);

		// function that returns the name of the publication using a const char* pointer; cannot change class state
		const char* name() const;

		// 
		void shelfNo(int value);


	public:

		// -- constructors/destructors --
		PubRecord();	// sets class to an empty state
		virtual ~PubRecord();	// ensure no memory leak
		PubRecord(const PubRecord&); // copy constructor, safely copies a PubRecord

		PubRecord& operator=(const PubRecord&); // assignment operator overload, assigns a PubRecord to another PubRecord

		// localize copy constructor and copy assignment logic
		void init(const PubRecord& source);

		// -- member functions --

		// sets the type of media publication is published on
		void mediaType(int media);

		// returns the type of media publication is published on
		int mediaType() const;

		// returns the integer member variable for the shelf number of publication
		int shelfNo() const;

		// receives 3-digit integer from console, if invalid shelf number, ask until valid
		void readShelfNo();

		// -- overloaded operators --

		// compares character to return value of recID(); returns true if equal
		bool operator==(char c);

		// compares strings, if received string is substring of the name of the class, return true
		bool operator==(const char* name);

		// return true if PubRecord is not empty; returns false if empty
		operator bool() const;

		// -- pure virtual functions --
		virtual void checkIn() = 0;
		virtual void checkOut() = 0;
	};

} // end namespace


#endif