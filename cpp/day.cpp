
/*!
 *    _________               /\  
 *   /   _____/__ ____________)/  
 *   \_____  \|  |  \____ \__  \  
 *   /        \  |  /  |_> > __ \_
 *  /_______  /____/|   __(____  /
 *          \/      |__|       \/  
 *
 *  \author    Michael E. Cotterell <mepcott@uga.edu>
 *  \date      2016-10-18
 *  \warning   Requires strptime(3) from Linux glibc.
 */

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

const char days [7][4] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

int julian_day(int y, int m, int d);

int main(int argc, const char * argv[]) {

  struct tm tm;                         // tm structure
  char date [11];                       // date string
    
  int y = atoi(argv[1]);                // year as C string
  int m = atoi(argv[2]);                // month as C string
  int d = atoi(argv[2]);                // day as C string

  sprintf(date, "%d-%d-%d", y, m, d);   // create date string
  strptime(date, "%Y-%m-%d", &tm);      // extract tm structure

  int gday = tm.tm_wday;                // num days since SUN (Gregorian)
  int jday = julian_day(y, m, d);       // num days since SUN (Julian)

  cout << "     Date: " << date << endl;
  cout << "Gregorian: " << gday << " (" << days[gday] << ")" << endl; 
  cout << "   Julian: " << jday << " (" << days[jday] << ")" << endl;
  
  return EXIT_SUCCESS;
    
} // main

/**
 * Compute the Julian Day.
 * @see https://en.wikipedia.org/wiki/Julian_day#Converting_Julian_or_Gregorian_calendar_date_to_Julian_day_number
 */
int julian_day(int year, int month, int day) {
  int a = floor((14 - month) / 12);
  int y = year + 4800 - a;
  int m = month + 12 * a - 3;
  int j = day
    + floor((153 * m + 2) / 5)
    + (365 * y)
    + floor(y / 4)
    - 32083;
  return (j + 1) % 7;
} // julian_day

