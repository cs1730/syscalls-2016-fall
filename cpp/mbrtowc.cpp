#include <iostream>
#include <clocale>
#include <cstring>
#include <cwchar>
#include <fcntl.h>
#include <unistd.h>

const size_t BUFFSIZE = 1024;
//const size_t BUFFSIZE = 8;

// @see http://en.cppreference.com/w/cpp/string/multibyte/mbrtowc
int main(const int argc, const char * argv []) {
  std::setlocale(LC_ALL, "en_US.utf8");        // enable unicode
  const char * filename = argv[1];             // filename
  char buffer [BUFFSIZE];                      // read buffer
  int fd = (argc == 1) ? STDIN_FILENO : open(filename, O_RDONLY);
  size_t nbytes = 0;                           // # bytes read
  size_t nchars = 0;                           // # characters read
  while ((nbytes = read(fd, buffer, BUFFSIZE)) > 0) {
    std::mbstate_t state = std::mbstate_t();   // initialize state
    size_t len = 0;                            // # bytes processed
    wchar_t wc = 0;                            // multibyte character
    size_t sum = 0;                            // sum # bytes processed
    while((len = std::mbrtowc(&wc, buffer+sum, nbytes-sum, &state)) > 0) {
      if (len == (size_t) -2) break;           // incomplete wchar
      std::wcout << "Next " << len << " bytes are the character " << wc << std::endl;
      sum    += len;                           // accumulate sum
      nchars += 1;                             // increment character count
    } // while
    // handle incomplete wchar at end of buffer by seeking back a little
    if (sum < nbytes) lseek(fd, sum-nbytes, SEEK_CUR);
  } // while
  std::wcout << "nchars = " << nchars << std::endl;
  close(fd);
} // main

