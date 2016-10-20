
#include <ios>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sys/types.h>
#include <dirent.h>

using std::cout;
using std::endl;
using std::string;

void nope_out(const string & prefix);

int main(const int argc, const char * argv []) {

  // turn off buffering for cout
  cout.setf(std::ios::unitbuf);

  const char * dirname = argv[1];
  DIR * dirp = nullptr;
  struct dirent * direntp = nullptr;

  if ((dirp = opendir(dirname)) == nullptr) {
    nope_out("opendir");
  } // if

  // DO STUFF
  while ((direntp = readdir(dirp)) != nullptr) {
    cout << direntp->d_ino << " "
	 << direntp->d_name << endl;
  } // while

  if (closedir(dirp) == -1) {
    nope_out("closedir");
  } // if
  
  return EXIT_SUCCESS;
  
} // main

void nope_out(const string & prefix) {
  perror(prefix.c_str());
  // exit(EXIT_FAILURE);
} // nope_out

