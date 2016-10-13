#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>

using std::cout;
using std::endl;

int main(const int argc, const char * argv []) {

  // read stuff
  char buffer [10];
  int nbytes;

  while ((nbytes = read(STDIN_FILENO, buffer, 10)) > 0) {
    write(STDOUT_FILENO, buffer, nbytes);
  } // while

  if (nbytes == -1) {
    cout << "read error" << endl;
  } // if
  
  return EXIT_SUCCESS;
} // main


