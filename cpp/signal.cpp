
#include <iostream>
#include <cstdlib>
#include <signal.h>

using std::cout;
using std::endl;

void my_handler(int signo) {
  cout << "NOPE!!" << endl;
} // my_handler

int main() {
  //signal(SIGINT, (void (*)(int)) 42);
  signal(SIGINT, my_handler);
  // sighandler_t old_handler = signal(SIGINT, SIG_IGN);
  //  signal(SIGINT, old_handler);
  // signal(SIGINT, SIG_DFL);
  while (true);
  return EXIT_SUCCESS;
} // main

