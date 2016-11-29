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
  int backup, ofd, cfd;

  // backup standard output
  if ((backup = dup(STDOUT_FILENO)) == -1) nope_out("dup");

  // set user file creation mask
  umask(0); // always succeeds! (see umask(2))
  
  if ((ofd = open(filename, O_WRONLY | O_CREAT, 0666)) == -1) {
    nope_out("open");
  } // if

  // print to screen
  cout << "before dup2" << endl;

  // duplicate ofd into standard output;
  // standard out will become a duplicate of ofd
  if (dup2(ofd, STDOUT_FILENO) == -1) nope_out("dup2");

  // alternative to dup2...
  // close(STDOUT_FILENO);
  // STDOUT_FILENO = dup(ofd);
  

  // print to ofd's file
  cout << "after dup2" << endl;

  // duplicate backup into standard output;
  // standard out will become a duplicate of backup
  if (dup2(backup, STDOUT_FILENO) == -1) nope_out("dup2"); 

  // print to screen
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

