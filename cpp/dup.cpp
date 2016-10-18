#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

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

  umask(0); // TODO error checking
  if ((ofd = open(filename, O_WRONLY | O_CREAT, 0666)) == -1) {
    nope_out("open");
  } // if

  cout << "before dup2" << endl;

  int backup = dup(STDOUT_FILENO); // TODO error checking
  dup2(ofd, STDOUT_FILENO); // TODO error checking

  cout << "after dup2" << endl;
  
  dup2(backup, STDOUT_FILENO); // TODO error checking

  cout << "back to normal" << endl;
  
  if ((cfd = close(ofd)) == -1) {
    nope_out("close");
  } // if

  return EXIT_SUCCESS;
  
} // main

void nope_out(const string & prefix) {
  perror(prefix.c_str());
  exit(EXIT_FAILURE);
} // nope_out

