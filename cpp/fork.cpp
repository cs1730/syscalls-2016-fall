#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

using std::cout;
using std::endl;

int globvar = 6;

int main() {

  int locvar = 3;
  pid_t pid;

  cout << "before fork"; // << endl;

  if ((pid = fork()) == -1) { // error
    perror("FORK ERROR");
  } else if (pid == 0) {    // in child process
    ++globvar;
    ++locvar;
    cout << " in child ";
  } else {                  // in parent process
    sleep(3);
    cout << " in parent ";
  } // if

  cout << endl;
  cout << "after fork: "
       << "fork() = "  << pid      << ", "
       << "mypid = "   << getpid() << ", "
       << "globvar = " << globvar  << ", "
       << "locvar = "  << locvar   << endl;

  return EXIT_SUCCESS;

} // main

