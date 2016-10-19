
/*! 
 *  \author    Michael E. Cotterell <mepcott@uga.edu>
 *  \date      2016
 *  \warning   May only work properly on Linux systems
 */

#include <iostream>
#include <cstdlib>

using namespace std;

const char days [7][4] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

int main(int argc, const char * argv[]) {

  struct tm tm;                         // tm structure
  char date [11];                       // date string
    
  char y [] = "2016";                   // year as C string
  char m [] = "10";                     // month as C string
  char d [] = "01";

  sprintf(date, "%s-%s-%s", y, m, d);   // create date string
  strptime(date, "%Y-%m-%d", &tm);      // extract tm structure

  cout << date << endl;                 // date string
  cout << tm.tm_wday << endl;           // num days since SUN
  cout << *(days + tm.tm_wday) << endl; // day of week
    
  return EXIT_SUCCESS;
    
} // main

