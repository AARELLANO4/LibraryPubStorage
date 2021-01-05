// Final Project Milestone 1 
// Date Module
// File	Date.cpp
// Version 2.0
// Author	Alexis Arellano
// Revision History
// -----------------------------------------------------------
// Name						   Date                 Reason
// Alexis Arellano             2019/11/15           Debugging
/////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
using namespace std;
#include "Date.h"

namespace sdds {
   
   // === private functions
   int Date::daysSince0001_1_1()const { // Rata Die day since 0001/01/01 
	   int ty = m_year;
	   int tm = m_mon;
	   if (tm < 3) {
		   ty--;
		   tm += 12;
	   }
	   return 365 * ty + ty / 4 - ty / 100 + ty / 400 + (153 * tm - 457) / 5 + m_day - 306;
   }

   bool Date::validate() {
	   errCode(NO_ERROR);
	   if (m_year < MIN_YEAR || m_year > m_CUR_YEAR) {
		   errCode(YEAR_ERROR);
	   }
	   else if (m_mon < 1 || m_mon > 12) {
		   errCode(MON_ERROR);
	   }
	   else if (m_day < 1 || m_day > mdays()) {
		   errCode(DAY_ERROR);
	   }
	   return !bad();
   }

   void Date::errCode(int readErrorCode) {
	   m_ErrorCode = readErrorCode;
   }

   int Date::curYear()const {
	   time_t t = time(NULL);
	   tm lt = *localtime(&t);
	   return lt.tm_year + 1900;
   }

   bool Date::bad()const {
	   return m_ErrorCode != 0;
   }

   int Date::mdays()const {
	   int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
	   int mon = m_mon >= 1 && m_mon <= 12 ? m_mon : 13;
	   mon--;
	   return days[mon] + int((mon == 1) * ((m_year % 4 == 0) && (m_year % 100 != 0)) || (m_year % 400 == 0));
   }

   void Date::setToToday() {
	   time_t t = time(NULL);
	   tm lt = *localtime(&t);
	   m_day = lt.tm_mday;
	   m_mon = lt.tm_mon + 1;
	   m_year = lt.tm_year + 1900;
	   errCode(NO_ERROR);
   }
   
  

   // === constructors/destructors ===

   Date::Date() :m_CUR_YEAR(curYear()) {
	   setToToday();
   }
   Date::Date(int year, int mon, int day) : m_CUR_YEAR(curYear()) {
	   m_year = year;
	   m_mon = mon;
	   m_day = day;
	   validate();
   }

   // === public functions ===
   int Date::errCode()const {
	   return m_ErrorCode;
   }

   const char* Date::dateStatus()const {
	   return DATE_ERROR[errCode()];
   }
   int Date::currentYear()const {
	   return m_CUR_YEAR;
   }

   istream& Date::read(istream& is) {

	   // 1. Set error code to NO_ERROR
	   errCode(NO_ERROR);
	   

	   is >> m_year;
	   is.ignore();
           is >> m_mon;
           is.ignore();
           is >> m_day;


	   if (is.fail()) {
		   is.clear();
		   errCode(CIN_FAILED);
	   }
	   else {
		   validate();
	   }
	   
	   char ch;
	   do {
		   ch = is.get();
	   } while (ch != '\n');
	   return is;
   }

   std::ostream& Date::write(std::ostream& os) const {
	   if (m_ErrorCode != 0) {
		   os << "Invalid Date Object";
	   }


	   else {
		   os << m_year;
		   os << '/' << std::setfill('0') << std::setw(2) << m_mon;
		   os << '/' << std::setfill('0') << std::setw(2) << m_day;
	   }
	   return os;
   }

   int Date::pubDaysSince() const {
	   int daysSince;
	   daysSince = daysSince0001_1_1();
	   return daysSince;
   }

   Date::operator bool() {
	   bool check = validate();
	   return check;
   }

   // === OPERATOR OVERLOADS ===
   bool operator==(const Date& Date1, const Date& Date2) {
	   
	   int result1 = Date1.pubDaysSince();
	   int result2 = Date2.pubDaysSince();
	   bool equalTo = false;

	   if (result1 == result2) {
		   equalTo = true;
	   }
	   
	   return equalTo;
   }

   bool operator!=(const Date& Date1, const Date& Date2) {
	   int result1 = Date1.pubDaysSince();
	   int result2 = Date2.pubDaysSince();

	   bool notEqualTo = false;

	   if (result1 != result2) {
		   notEqualTo = true;
	   }

	   return notEqualTo;
   }

   bool operator>=(const Date& Date1, const Date& Date2) {
	   int result1 = Date1.pubDaysSince();
	   int result2 = Date2.pubDaysSince();
	   bool greaterEqualTo = false;

	   if (result1 >= result2) {
		   greaterEqualTo = true;
	   }
	   return greaterEqualTo;
   }

   bool operator<=(const Date& Date1, const Date& Date2) {
	   int result1 = Date1.pubDaysSince();
	   int result2 = Date2.pubDaysSince();
	   bool lessEqualTo = false;

	   if (result1 <= result2) {
		   lessEqualTo = true;
	   }

	   return lessEqualTo;
   }

   bool operator<(const Date& Date1, const Date& Date2) {
	   int result1 = Date1.pubDaysSince();
	   int result2 = Date2.pubDaysSince();
	   bool lessThan = false;

	   if (result1 < result2) {
		   lessThan = true;
	   }

	   return lessThan;
   }

   bool operator>(const Date& Date1, const Date& Date2) {
	   int result1 = Date1.pubDaysSince();
	   int result2 = Date2.pubDaysSince();
	   bool greaterThan = false;

	   if (result1 > result2) {
		   greaterThan = true;
	   }

	   return greaterThan;
   }

   int Date::operator-(const Date& Date1)const {
	   int result1 = this->daysSince0001_1_1();
	   int result2 = Date1.daysSince0001_1_1();
	   int difference;

	   difference = result1 - result2;   

	return difference;
   }

   ostream& operator<<(ostream& os, const Date& date) {
	   date.write(os);
	   return os;
   }
   
   istream& operator>>(istream& is, Date& date) {
	   date.read(is);
	   return is;
   }
   
}
