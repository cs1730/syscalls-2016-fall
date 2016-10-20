
/*!
 *  \author CSCI 1730 Fall 2016
 *  \date   2016-10-20
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

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

  if ((ofd = open(filename, O_RDONLY)) == -1) {
    nope_out("open");
  } // if

  // DO STUFF HERE
  off_t size;

  if ((size = lseek(ofd, 0, SEEK_END)) == -1) {
    nope_out("lseek");
  } // if
  cout << size << endl;
  
  if ((cfd = close(ofd)) == -1) {
    nope_out("close");
  } // if

  return EXIT_SUCCESS;
  
} // main

void nope_out(const string & prefix) {
  perror(prefix.c_str());
  // exit(EXIT_FAILURE);
} // nope_out

