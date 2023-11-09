/* P3:
 * File: calendar.cpp
 * ------------------
 * This file implements the p1calendar.h interface
 */


//When I don't return the value of a function with &, it's still runtime error (sometimes).
#include <string>
#include <iostream>
#include <sstream>
// #include "CSC3002OJActive/assignment2/lib.h" // for OJ test
// #include "CSC3002OJActive/assignment2/calendar.h" // for OJ test
#include "lib.h"      // For local test
#include "calendar.h" // For local test
using namespace std;

Month stringToMonth(string s)
{
   if (s == "JANUARY")
   {
      return JANUARY;
   }
   if (s == "FEBRUARY")
   {
      return FEBRUARY;
   }
   if (s == "MARCH")
   {
      return MARCH;
   }
   if (s == "APRIL")
   {
      return APRIL;
   }
   if (s == "MAY")
   {
      return MAY;
   }
   if (s == "JUNE")
   {
      return JUNE;
   }
   if (s == "JULY")
   {
      return JULY;
   }
   if (s == "AUGUST")
   {
      return AUGUST;
   }
   if (s == "SEPTEMBER")
   {
      return SEPTEMBER;
   }
   if (s == "OCTOBER")
   {
      return OCTOBER;
   }
   if (s == "NOVEMBER")
   {
      return NOVEMBER;
   }
   if (s == "DECEMBER")
   {
      return DECEMBER;
   }
}

/* TODO PART:
 * Implementation notes: monthToString
 * -----------------------------------
 * The monthToString function must return some value if the month does not
 * match any of the enumeration constants.  Here, as in the Direction
 * type, the function returns ???.
 */
string monthToString(Month month)
{
   // TODO
   switch (month)
   {
   case 1:
      return "JANUARY";
      break;
   case 2:
      return "FEBRUARY";
      break;
   case 3:
      return "MARCH";
      break;
   case 4:
      return "APRIL";
      break;
   case 5:
      return "MAY";
      break;
   case 6:
      return "JUNE";
      break;
   case 7:
      return "JULY";
      break;
   case 8:
      return "AUGUST";
      break;
   case 9:
      return "SEPTEMBER";
      break;
   case 10:
      return "OCTOBER";
      break;
   case 11:
      return "NOVEMBER";
      break;
   case 12:
      return "DECEMBER";
      break;
   default:
      return "???";
      break;
   }
   return NULL;
}

// 带有int的是在i++
Month operator++(Month &month, int)
{
   Month result = month;
   // TODO
   if (month == DECEMBER)
   {
      month = Month(1);
   }else{
   month = Month(month + 1);
   }
   return result;
}

/*
 * Implementation notes: Constructors
 * ----------------------------------
 * There are three constructors for the Date class.  The default
 * constructor creates a Date with a zero internal value that must
 * be assigned a new value before it is used.  The others initialize
 * the date from the arguments by calling the private initDate method.
 */

Date::Date()
{
   initDate(1, JANUARY, 1900);
}

Date::Date(int day, Month month, int year)
{
   initDate(day, month, year);
}

Date::Date(Month month, int day, int year)
{
   initDate(day, month, year);
}

/*
 * TODO function
 * Implementation notes: getDay, getMonth
 * --------------------------------------
 *
 */

int Date::getDay()
{
   // TODO
   return day;
}

/*
 * TODO function
 * Method: getMonth
 * Usage: Month month = date.getMonth();
 * -------------------------------------
 * Returns the month.
 */

Month Date::getMonth()
{
   // TODO
   return month;
}

int Date::getYear()
{
   // TODO
   return year;
}

/*
 * TODO function
 * Implementation notes: toString
 * ------------------------------
 * The toString method uses the getters to perform the translation into
 * day/month/year values.
 */

string Date::toString()
{
   // TODO
   ostringstream os;
      os << this -> getDay() << "-";
   switch (this -> getMonth())
   {
   case JANUARY:
      os << "Jan";
      break;
   case FEBRUARY:
      os << "Feb";
      break;
   case MARCH:
      os << "Mar";
      break;
   case APRIL:
      os << "Apr";
      break;
   case MAY:
      os << "May";
      break;
   case JUNE:
      os << "Jun";
      break;
   case JULY:
      os << "Jul";
      break;
   case AUGUST:
      os << "Aug";
      break;
   case SEPTEMBER:
      os << "Sep";
      break;
   case OCTOBER:
      os << "Oct";
      break;
   case NOVEMBER:
      os << "Nov";
      break;
   case DECEMBER:
      os << "Dec";
      break;
   default:
      os << "???";
      break;
   }

   os << "-" << this -> getYear();
   return os.str();
}

void Date::initDate(int day, Month month, int yyyy)
{
   // TODO
   this->day = day;
   this->month = month;
   this->year = yyyy;
}

Date operator+(Date date, int delta)
{
   // TODO
   int day = date.getDay();
   Month month = date.getMonth();
   int year = date.getYear();
   while (delta != 0)
   {
      int dayInMonth = daysInMonth(month, year);
      day++;
      delta--;
      if (day > dayInMonth)
      {
         day = 1;
         if (month == DECEMBER)
         {
            month = JANUARY;
            year++;
         }
         else
         {
            month++;
         }
      }
   }
   return Date(month, day, year);
}

Date operator-(Date date, int delta)
{
   // TODO
   int day = date.getDay();
   Month month = date.getMonth();
   int year = date.getYear();
   while (delta != 0)
   {
      day--;
      if (day <= 0)
      {
         if (month == JANUARY)
         {
            year--;
            month = DECEMBER;
         }
         else
         {
            month = Month(month - 1);
         }
         day = daysInMonth(month, year);
      }
      delta--;
   }
   return Date(month, day, year);
}

int operator-(Date d1, Date d2)
{
   // TODO
   int count = 0;
   if (d1 > d2)
   {
      while (d1 != d2)
      {
         d1--;
         count++;
      }
   }
   else
   {
      while (d1 != d2)
      {
         d1++;
         count--;
      }
   }
   return count;
}

Date &operator+=(Date &date, int delta)
{
   // TODO
   date = date + delta;
   return date;
}

Date &operator-=(Date &date, int delta)
{
   // TODO
   date = date - delta;
   return date;
}
// ? i++ and ++i
Date operator++(Date &date)
{
   // TODO ++i
   date = date + 1;
   return date;
}

Date operator++(Date &date, int)
{
   // TODO 此为i++
   Date result = date;
   date += 1;
   return result;
}

Date operator--(Date &date)
{
   // TODO
   date = date - 1;
   return date;
}

Date operator--(Date &date, int)
{
   // TODO
   Date result = date;
   date = date - 1;
   return result;
}

bool operator==(Date d1, Date d2)
{
   // TODO
   return d1.getDay() == d2.getDay() && d1.getMonth() == d2.getMonth() && d1.getYear() == d2.getYear();
}

bool operator!=(Date d1, Date d2)
{
   // TODO
   return !(d1 == d2);
}

bool operator<(Date d1, Date d2)
{
   // TODO
   return !(d1 >= d2);
}

bool operator<=(Date d1, Date d2)
{
   // TODO
   return !(d1 > d2);
}

bool operator>(Date d1, Date d2)
{
   // TODO
   if (d1.getYear() > d2.getYear())
   {
      return true;
   }
   else if (d1.getYear() < d2.getYear())
   {
      return false;
   }
   else
   {
      if (d1.getMonth() > d2.getMonth())
      {
         return true;
      }
      else if (d1.getMonth() < d2.getMonth())
      {
         return false;
      }
      else
      {
         if (d1.getDay() > d2.getDay())
         {
            return true;
         }
         else if (d1.getDay() < d2.getDay())
         {
            return false;
         }
         else
         {
            return false;
         }
      }
   }
}

bool operator>=(Date d1, Date d2)
{
   // TODO
   return d1 > d2 || d1 == d2;
}

std::ostream &operator<<(std::ostream &os, Date date)
{
   // TODO
   os << date.toString();
   return os;
}

/*
 * TODO function
 * Implementation notes: daysInMonth
 * ---------------------------------
 * This function is a reasonably literal translation of the old rhyme:
 *
 *    Thirty days has September
 *    April, June, and November
 *    All the rest have 31
 *    Excepting February alone
 *    Which has 28 in fine
 *    And each leap year 29
 */

int daysInMonth(Month month, int year)
{
   // TODO
   if(isLeapYear(year) && month == FEBRUARY){
      return 29;
   }
   switch (month)
   {
   case 1:
      return 31;
      break;
   case 3:
      return 31;
      break;
   case 5:
      return 31;
      break;
   case 7:
      return 31;
      break;
   case 8:
      return 31;
      break;
   case 10:
      return 31;
      break;
   case 12:
      return 31;
      break;
   case 2:
      return 28;
      break;
   case 4:
      return 30;
      break;
   case 6:
      return 30;
      break;
   case 9:
      return 30;
      break;
   case 11:
      return 30;
      break;
   default:
      return 0;
      break;
   }
   
   return 0;
}

/* TODO PART:
 * Implementation notes: isLeapYear
 * --------------------------------
 * This function simply encodes the rule for determining leap years:
 * a leap year is any year divisible by 4, except for years ending in 00,
 * in which case the year must be divisible by 400.
 */

bool isLeapYear(int year)
{
   // TODO
   if (year % 100 == 0)
   {
      if (year % 400 == 0)
      {
         return true;
      }
      else
      {
         return false;
      }
   }
   else
   {
      if (year % 4 == 0)
      {
         return true;
      }
      else
      {
         return false;
      }
   }
   return false;
}

/* DO NOT modify this main() part */
int main()
{
   int id;
   cin >> id;
   int day, year;
   string mon;
   cin >> day >> mon >> year;

   if (id == 1)
   {
      for (Month month = JANUARY; month <= DECEMBER; month = Month(month + 1))
      {
         cout << monthToString(month) << " has " << daysInMonth(month, year)
              << " days." << endl;
      }
   }
   else if (id == 2)
   {
      Date moonLanding(day, stringToMonth(mon), year);
      cout << "moonLanding = " << moonLanding.toString() << endl;
   }
   else if (id == 3)
   {
      Date moonLanding(day, stringToMonth(mon), year);
      cin >> mon >> day >> year;
      Date kennedyAssassination(stringToMonth(mon), day, year);
      cin >> mon >> day >> year;
      Date newYearsEve(stringToMonth(mon), day, year);
      cin >> day >> mon >> year;
      Date inaugurationDay(day, stringToMonth(mon), year);
      cin >> day >> mon >> year;
      Date electionDay(day, stringToMonth(mon), year);
      cout << "moonLanding = " << moonLanding << endl;
      cout << "kennedyAssassination = " << kennedyAssassination << endl;
      cout << boolalpha;
      cout << "moonLanding < kennedyAssassination = "
           << (moonLanding < kennedyAssassination) << endl;
      cout << "moonLanding > kennedyAssassination = "
           << (moonLanding > kennedyAssassination) << endl;
      cout << "moonLanding == kennedyAssassination = "
           << (moonLanding == kennedyAssassination) << endl;
      cout << "moonLanding == moonLanding = "
           << (moonLanding == moonLanding) << endl;
      cout << "inaugurationDay - electionDay = "
           << (inaugurationDay - electionDay) << endl;
      Date day = newYearsEve;
      cout << "New Year's Eve = " << day++ << endl;
      cout << "New Year's Day = " << day << endl;
      for (Date d = electionDay; d <= inaugurationDay; d++)
      {
         cout << d << endl;
      }
   }
}
