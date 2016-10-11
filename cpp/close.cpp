#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>

using std::cout;
using std::endl;

int main(const int argc, const char * argv []) {

  if (argc != 2) {
    cout << "Usage: " << argv[0] << " FILE" << endl;
    exit(EXIT_FAILURE);
  } // if

  const char * filename = argv[1];
  int fd = open(filename, O_RDONLY);

  if (fd != -1) {
    cout << "Opened " << filename << "; "
	 << "fd = " << fd << "; "
	 << "error = " << strerror(errno) 
	 << endl;
  } else {
    cout << "Could not open " << filename << "; "
	 << "fd = " << fd  << " (should be -1); "
	 << "error = " << strerror(errno) 
	 << endl;
    //exit(EXIT_FAILURE);
  } // if

  int cfd = close(fd);

  if (cfd != -1) {
    cout << "Closed " << filename << "; "
	 << "fd = " << cfd << "; "
	 << "error = " << strerror(errno) 
	 << endl;
  } else {
    cout << "Could not close " << filename << "; "
	 << "fd = " << cfd  << " (should be -1); "
	 << "error = " << strerror(errno) 
	 << endl;
    exit(EXIT_FAILURE);
  } // if

  return EXIT_SUCCESS;
} // main


