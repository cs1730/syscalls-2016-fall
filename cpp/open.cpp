
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using std::cout;
using std::endl;

int main(const int argc, const char * argv []) {
  const char * filename = argv[1];
  int fd = -1;

  fd = open(filename, O_RDONLY | O_CREAT, 0777);
  cout << "fd = " << fd << " "
       << "strerror = " << strerror(errno) << endl;

  return EXIT_SUCCESS;
} // main

