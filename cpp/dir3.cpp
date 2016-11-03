
#include <iostream>
#include <cstdlib>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include "nope.h"

using std::cout;
using std::endl;

void copy_dir(const char * source, const char * target, bool copy_into = false);
void copy_file(const char * source, const char * target);

// @TODO copy_into parameter should be triggered, not explicitly set
int main(const int argc, const char * argv []) {
  cout.setf(std::ios::unitbuf);          // turn off buffering for cout
  const char * source = argv[1];         // source directory
  const char * target = argv[2];         // target directory
  copy_dir(source, target, true);        // copy the directory
  return EXIT_SUCCESS;
} // main

// @TODO probably should handle errors better
// @TODO needs to print out the initial mkdirs
void copy_dir(const char * source, const char * target, bool copy_into) {

  DIR * dirp = nullptr;                  // directory pointer
  struct dirent * direntp = nullptr;     // directory entry pointer
  char spath [PATH_MAX];                 // directory entry path (source)
  char tpath [PATH_MAX];                 // target path

  if ((dirp = opendir(source)) == nullptr) nope_out("opendir");

  while ((direntp = readdir(dirp)) != nullptr) {
    const char * ename = direntp->d_name;
    if ((strcmp(ename, ".") != 0) && (strcmp(ename, "..") != 0)) {

      // construct modified source path
      strcpy(spath, source);             // make a copy of source path
      strcat(spath, "/");                // append "/"
      strcat(spath, ename);              // append entry name

      // construct modified target path
      strcpy(tpath, target);             // make a copy of target path
      if (copy_into) {                   // handle copy into scenario
	// @TODO handle when source is "."
	// @TODO handle when source is absolute path (maybe use basename and realpath?)
	strcat(tpath, "/");              // append "/"
	strcat(tpath, basename(source)); // append basename of source path
      } // if
      strcat(tpath, "/");                // append "/"
      strcat(tpath, ename);              // append entry name
      
      if (direntp->d_type == DT_DIR) {
	cout << "[mkdir] " << tpath << endl;
	copy_dir(spath, tpath);          // recurse on the subdirectory
      } else {
	copy_file(spath, tpath);
      } // if
      
    } // if
  } // while

  if (closedir(dirp) == -1) nope_out("closedir");
  
} // copy_dir

void copy_file(const char * source, const char * target) {
  cout << "[read] " << source
       << " -> "
       << "[write] " << target
       << endl;
} // copy_file

