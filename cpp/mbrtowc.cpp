#include <iostream>
#include <clocale>
#include <cstring>
#include <cwchar>
#include <fcntl.h>
#include <unistd.h>

const size_t BUFFSIZE = 1024;

int main(const int argc, const char * argv []) {
  std::setlocale(LC_ALL, "en_US.utf8");       // enable unicode
  const char * filename = argv[1];            // filename
  char buffer [BUFFSIZE];                     // read buffer
  int fd = open(filename, O_RDONLY);          // file descriptor
  int nbytes = 0;                             // # bytes read
  int chars = 0;                              // # characters read
  while ((nbytes = read(fd, buffer, BUFFSIZE)) > 0) {
    std::mbstate_t state = std::mbstate_t();  // initialize state
    char * ptr = buffer;                      // start of sliding window
    const char* end = ptr + std::strlen(ptr); // end of sliding window
    int len = 0;                              // # bytes processed
    wchar_t wc = '\0';                        // multibyte character
    while((len = std::mbrtowc(&wc, ptr, end-ptr, &state)) > 0) {
      std::wcout << "Next " << len << " bytes are the character " << wc << std::endl;
      ptr += len;                             // move onto the next one
      chars += 1;                             // increment character count
      if (ptr > end) break;                   // don't go past the end
    } // while
  } // while
  std::wcout << "# chars = " << chars << std::endl;
  close(fd);
} // main

