
#include <ios>
#include <iostream>
#include <string>
#include <cstdlib>

using std::cout;
using std::endl;
using std::string;

void nope_out(const string & prefix);

int main(const int argc, const char * argv []) {

  // turn off buffering for cout
  cout.setf(std::ios::unitbuf);

  return EXIT_SUCCESS;
  
} // main

void nope_out(const string & prefix) {
  perror(prefix.c_str());
  exit(EXIT_FAILURE);
} // nope_out

