#include <iostream>
#include <clocale>
#include <cstring>
#include <cwchar>
#include <fcntl.h>
#include <unistd.h>

const size_t BUFFSIZE = 1024;

int main(const int argc, const char * argv []) {
  std::setlocale(LC_ALL, "en_US.utf8");
  const char * filename = argv[1];
  char buffer [BUFFSIZE];
  int fd = open(filename, O_RDONLY);
  int nbytes = 0;
  int chars = 0;
  while ((nbytes = read(fd, buffer, BUFFSIZE)) > 0) {
    std::mbstate_t state = std::mbstate_t();
    char * ptr = buffer;
    const char* end = ptr + std::strlen(ptr);
    int len;
    wchar_t wc;
    while((len = std::mbrtowc(&wc, ptr, end-ptr, &state)) > 0) {
      std::wcout << "Next " << len << " bytes are the character " << wc << std::endl;
      ptr += len;
      chars += 1;
      if (ptr > end) break;
    } // while
  } // while
  std::wcout << "# chars = " << chars << std::endl;
  close(fd);
} // main

