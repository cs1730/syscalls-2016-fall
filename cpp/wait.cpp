#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using std::cout;
using std::endl;
using std::string;

void print_now(string s) {
  if (write(STDOUT_FILENO, s.c_str(), s.size()) == -1) {
    perror("println");
  } // if
} // print

void println_now(string s = "") {
  print_now(s + "\n");
} // println

int main() {

  pid_t pid;

  println_now("before fork");

  if ((pid = fork()) < 0) { // error
    perror("FORK ERROR");
    exit(EXIT_FAILURE);
  } else if (pid == 0) {
    // in child
    for (int i = 0; i < 100; ++i) {
      cout << "i = "        << i         << ", "
	   << "my pid = "   << getpid()  << ", "
	   << "fork = "     << pid       << ", "
	   << "ppid = "     << getppid() << endl;
    } // for
    exit(42);
  } else {
    // in parent
    for (int i = 0; i < 100; ++i) {
      cout << "parent" << endl;
    } // for
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status)) {
      cout << "child exited with status = " << WEXITSTATUS(status) << endl;
    } // if
  } // if

  return EXIT_SUCCESS;

} // main

