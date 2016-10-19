
/*! 
 *  \author    Michael E. Cotterell <mepcott@uga.edu>
 *  \date      2016
 *  \warning   May only work properly on Linux systems.
 */

#include <iostream>
#include <cstdlib>

using namespace std;

const char days [7][4] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

int main(int argc, const char * argv[]) {

  struct tm tm;                         // tm structure
  char date [11];                       // date string
    
  char y [] = "1752";                   // year as C string
  char m [] = "08";                     // month as C string
  char d [] = "01";                     // day as C string

  sprintf(date, "%s-%s-%s", y, m, d);   // create date string
  strptime(date, "%Y-%m-%d", &tm);      // extract tm structure

  int gday = tm.tm_wday;                // num days since SUN (Gregorian)
  int jday = (tm.tm_wday + 4) % 7;      // num days since SUN (Julian)

  cout << "     Date: " << date << endl;
  cout << "Gregorian: " << gday << " (" << *(days + gday) << ")" << endl; 
  cout << "   Julian: " << jday << " (" << *(days + jday) << ")" << endl;
  
  return EXIT_SUCCESS;
    
} // main

