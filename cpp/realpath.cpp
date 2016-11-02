
#include <iostream>
#include <cstdlib>
#include <dirent.h>

using namespace std;

int main(const int argc, const char * argv []) {
  char path [PATH_MAX];
  realpath(argv[1], path);
  cout << path << endl;
  return EXIT_SUCCESS;
} // main

