
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <signal.h>

using std::cout;
using std::endl;

int main() {
  // TODO setup signal handler for SIGINT (Interrupt Signal)
  while (true) pause(); // wait for signal
  return EXIT_SUCCESS;
} // main

