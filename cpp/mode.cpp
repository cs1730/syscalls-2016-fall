
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>

using std::cout;
using std::endl;
using std::oct;
using std::setw;
using std::setfill;

int main(const int argc, const char * argv []) {

  if (argc != 2) {
    cout << "Usage: " << argv[0] << " FILE" << endl;
    exit(EXIT_FAILURE);
  } // if
  
  struct stat buffer;
  if (stat(argv[1], &buffer) == -1) {
    perror("stat");
    exit(EXIT_FAILURE);
  } // if

  mode_t perms = buffer.st_mode & 07777;

  cout << "S_ISUID 4000 " << ((perms & S_ISUID) ? "*": "") << endl;
  cout << "S_ISGID 2000 " << ((perms & S_ISGID) ? "*": "") << endl;
  cout << "S_ISVTX 1000 " << ((perms & S_ISVTX) ? "*": "") << endl;
  cout << "S_IRUSR 0400 " << ((perms & S_IRUSR) ? "*": "") << endl;
  cout << "S_IWUSR 0200 " << ((perms & S_IWUSR) ? "*": "") << endl;
  cout << "S_IXUSR 0100 " << ((perms & S_IXUSR) ? "*": "") << endl;
  cout << "S_IRGRP 0040 " << ((perms & S_IRGRP) ? "*": "") << endl;
  cout << "S_IWGRP 0020 " << ((perms & S_IWGRP) ? "*": "") << endl;
  cout << "S_IXGRP 0010 " << ((perms & S_IXGRP) ? "*": "") << endl;
  cout << "S_IROTH 0004 " << ((perms & S_IROTH) ? "*": "") << endl;
  cout << "S_IWOTH 0002 " << ((perms & S_IWOTH) ? "*": "") << endl;
  cout << "S_IXOTH 0001 " << ((perms & S_IXOTH) ? "*": "") << endl;
  cout << "  PERMS "
       << oct << setw(4) << setfill('0')
       << perms
       << endl;
  
  return EXIT_SUCCESS;
  
} // main

