
#include <ios>
#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

extern const char ** environ;

int main(const int argc, const char * argv []) {
  
  // turn off buffering for cout
  cout.setf(std::ios::unitbuf);

  for (const char ** env = environ; *env != nullptr; ++env) {
    cout << *env << endl;
  } // for

  return EXIT_SUCCESS;
  
} // main


