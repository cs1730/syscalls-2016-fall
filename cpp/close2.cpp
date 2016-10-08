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
  int ofd, cfd;

  if ((ofd = open(filename, O_RDONLY)) != -1) {
    cout << "Opened " << filename << "; "
	 << "ofd = " << ofd << "; "
	 << "error = " << strerror(errno) 
	 << endl;
  } else {
    cout << "Could not open " << filename << "; "
	 << "ofd = " << ofd  << " (should be -1); "
	 << "error = " << strerror(errno) 
	 << endl;
    exit(EXIT_FAILURE);
  } // if

  if ((cfd = close(ofd)) != -1) {
    cout << "Closed " << filename << "; "
	 << "cfd = " << cfd << "; "
	 << "error = " << strerror(errno) 
	 << endl;
  } else {
    cout << "Could not close " << filename << "; "
	 << "cfd = " << cfd  << " (should be -1); "
	 << "error = " << strerror(errno) 
	 << endl;
    exit(EXIT_FAILURE);
  } // if

  return EXIT_SUCCESS;
} // main


