#include <iostream>
#include <clocale>
#include <cstring>
#include <cwchar>
#include <cwctype>
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
  size_t nwords = 0;                           // # words read
  size_t nlines = 0;                           // # lines read
  size_t n      = 0;          
  bool inword   = false;
  while ((n = read(fd, buffer, BUFFSIZE)) > 0) {
    std::mbstate_t state = std::mbstate_t();   // initialize state
    size_t len = 0;                            // # bytes processed
    wchar_t wc = 0;                            // multibyte character
    size_t sum = 0;                            // sum # bytes processed
    while((len = std::mbrtowc(&wc, buffer+sum, n-sum, &state)) > 0) {
      if (len == (size_t) -2) break;           // incomplete wchar
      if (wc == '\n') nlines += 1;
      if (!iswspace(wc)) {
	if (!inword) {
	  inword  = true;
	  nwords += 1;
	} // if
      } else if (inword) {
	inword = false;
      } // if
      std::wcout << "Next " << len << " bytes are the character " << wc << std::endl;
      sum    += len;                           // accumulate sum
      nchars += 1;                             // increment character count
    } // while
    // handle incomplete wchar at end of buffer by seeking back a little
    if (sum < n) lseek(fd, sum-n, SEEK_CUR);
    nbytes += sum;
  } // while
  std::wcout << "nlines = " << nlines << std::endl
	     << "nwords = " << nwords << std::endl
	     << "nchars = " << nchars << std::endl
	     << "nbytes = " << nbytes << std::endl;
  close(fd);
} // main

