
#include <iostream>
#include <cstdlib>
#include <signal.h>

using std::cout;
using std::endl;

void my_handler(int signo) {
  cout << "NOPE!!" << endl;
} // my_handler

int main() {
  // TODO setup signal handler for SIGINT (Interrupt Signal)
  while (true);
  return EXIT_SUCCESS;
} // main

