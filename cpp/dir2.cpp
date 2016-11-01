
#include <ios>
#include <iostream>
#include <string>
#include <cstdlib>
#include <climits>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include "nope.h"

using std::cout;
using std::endl;
using std::string;

void print_dir(const char * dirname, int level = 0);

int main(const int argc, const char * argv []) {
  cout.setf(std::ios::unitbuf);       // turn off buffering for cout
  const char * dirname = argv[1];     // get dir name from program argument
  print_dir(dirname);                 // print out the directory
  return EXIT_SUCCESS;
} // main

// @TODO probably should handle errors better
void print_dir(const char * dirname, int level) {

  DIR * dirp = nullptr;               // directory pointer
  struct dirent * direntp = nullptr;  // directory entry pointer
  char subdirname [PATH_MAX];         // subdirectory name

  if ((dirp = opendir(dirname)) == nullptr) nope_out("opendir");

  while ((direntp = readdir(dirp)) != nullptr) {
    const char * ename = direntp->d_name;
    if ((strcmp(ename, ".") != 0) && (strcmp(ename, "..") != 0)) {

      for (int i = 0; i < level; ++i) cout << "  ";
      cout << " |- " << ename << endl;

      if (direntp->d_type == DT_DIR) {
	for (int i = 0; i < level; ++i) cout << "  ";
	cout << "   \\" << endl;
	strcpy(subdirname, dirname);  // make a copy of dirname
	strcat(subdirname, "/");      // append "/"
	strcat(subdirname, ename);    // append entry name
	print_dir(subdirname, level + 1);
      } // if
      
    } // if
  } // while

  if (closedir(dirp) == -1) nope_out("closedir");
  
} // print_dir

