
#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
  char * path = realpath("realpath.cpp", nullptr);
  cout << path << endl;
  free(path);
  return EXIT_SUCCESS;
} // main

