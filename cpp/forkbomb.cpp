
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h>

void check();
void nope();
void bomb();

int main() {
  check();
  bomb();
  return EXIT_SUCCESS;
} // main

void check() {
  char hostname [5];
  gethostname(hostname, 4);
  hostname[4] = '\0';
  if (strcmp(hostname, "nike") == 0) {
    nope();
  } // if
} // check

void nope() {
  printf("NO, NO, NOPE! Don't run this on nike!\n");
  exit(EXIT_FAILURE);
} // nope

void bomb() {
  for(;;) {
    int * p = new int [1024 * 1024]; // +1 MB
    fork();                          // create child
    p[0] = 0;                        // force copy-on-write
  } // for
} // bomb

