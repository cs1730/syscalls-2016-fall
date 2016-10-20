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

int main(const int argc, const char * argv []) {

  if (argc != 2) {
    cout << "Usage: " << argv[0] << " FILE" << endl;
    exit(EXIT_FAILURE);
  } // if

  const char * filename = argv[1];
  int ofd, cfd;

  if ((ofd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644)) == -1) {
    nope_out("open");
  } // if

  // write it here
  int buffer [] = { 1, 2, 4, 8 };
  int nbytes = write(ofd, buffer, sizeof buffer);
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

