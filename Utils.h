
#ifndef _SDDS_UTILS_H
#define _SDDS_UTILS_H
#include <iostream>

namespace sdds
{
	// returns integer from user input, between min and max
	int getInt(int min, int max);

	// gets user input value for val, checks if its between min,max
	// if not in min/max, prints error message and prompts until val is valid
	int readInt(int& val, int min, int max, const char* ErrorMess);

	void readStr(char* str, int len, const char* errorMessage);

	long long readISBN(long long& val, long long min, long long max, const char* ErrorMess);
} // end namespace

#endif