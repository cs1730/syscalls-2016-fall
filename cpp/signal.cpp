
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <signal.h>

using std::cout;
using std::endl;

void my_handler(int signo) {
  cout << "NOPE!" << endl;
  switch (signo) {
  case  SIGINT: cout << "SIGINT"  << endl; break;
  case SIGQUIT: cout << "SIGQUIT" << endl; break;
  default:      cout << "WAT?"    << endl; break;
  } // switch
} // my_handler

int main() {
  signal(SIGINT, my_handler);  // handler for SIGINT (generate with C-c)
  signal(SIGQUIT, my_handler); // handler for SIGQUIT (generate with C-\)
  signal(SIGTSTP, SIG_IGN);    // ignore SIGTSTP (generate with C-z)
  //  while (true) pause(); // wait for signal
  for (int i = 0; true; ++i) cout << i << endl;
  return EXIT_SUCCESS;
} // main

