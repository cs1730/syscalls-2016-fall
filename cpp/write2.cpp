#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>

using std::cout;
using std::endl;
using std::string;

void nope_out(const string & prefix);

/**
 * For this example, in addition to seeing the error message, you can always
 * run `echo $?` after the program terminates to see the exit code that is 
 * returned by the program.
 */
int main(const int argc, const char * argv []) {

  // read it here
  char buffer [128];
  int nbytes;

  while ((nbytes = read(STDIN_FILENO, buffer, 128)) > 0) {
    write(STDOUT_FILENO, buffer, nbytes);
  } // while
  
  if (nbytes == -1) nope_out("read");

  return EXIT_SUCCESS;
  
} // main

void nope_out(const string & prefix) {
  perror(prefix.c_str());
  exit(EXIT_FAILURE);
} // nope_out

