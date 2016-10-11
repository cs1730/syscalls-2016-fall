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

  if (argc != 2) {
    cout << "Usage: " << argv[0] << " FILE" << endl;
    exit(EXIT_FAILURE);
  } // if

  const char * filename = argv[1];
  int ofd, cfd;

  if ((ofd = open(filename, O_RDONLY)) == -1) {
    nope_out("open");
  } // if

  // read it here
  char buffer [128];
  int nbytes;

  while ((nbytes = read(ofd, buffer, 127)) > 0) {
    buffer[nbytes] = '\0';
    // cout << "nbytes = " << nbytes << endl;
    cout << buffer;
  } // while
  
  if (nbytes == -1) nope_out("read");

  if ((cfd = close(ofd)) == -1) {
    nope_out("close");
  } // if

  return EXIT_SUCCESS;
  
} // main

void nope_out(const string & prefix) {
  perror(prefix.c_str());
  exit(EXIT_FAILURE);
} // nope_out

