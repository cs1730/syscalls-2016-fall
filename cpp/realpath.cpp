
#include <iostream>
#include <cstdlib>
#include <dirent.h>

using namespace std;

int main(const int argc, const char * argv []) {
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " FILE" << endl;
    exit(EXIT_FAILURE);
  } // if
  char path [PATH_MAX];
  realpath(argv[1], path);
  cout << path << endl;
  return EXIT_SUCCESS;
} // main

