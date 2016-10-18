#include <iostream>
#include <cstdlib>
#include <cerrno>
#include <unistd.h>

using std::cout;
using std::endl;
using std::string;

void nope_out(const string & prefix);

int main(const int argc, const char * argv []) {

  if (argc != 2) {
    cout << "Usage: " << argv[0] << " FILE" << endl;
    exit(EXIT_FAILURE);
  } // if

  const char * filename = argv[1];

  if (access(filename, F_OK) != -1) {
    cout << filename << " exists!" << endl;
  } else {
    cout << filename << " does NOT exist!" << endl;
  } // if

  return EXIT_SUCCESS;
  
} // main

void nope_out(const string & prefix) {
  perror(prefix.c_str());
  exit(EXIT_FAILURE);
} // nope_out

