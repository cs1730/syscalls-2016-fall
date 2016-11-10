
/* execve(2) example. Does NOT perform path resolution.
 */

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>

using std::cout;
using std::endl;

int main(int argc, char * argv [], char * envp[]) {

  char * filename = argv[1];

  cout << "filename: " << filename << endl;
  for (int i = 1; i < argc; ++i) {
    cout << (i-1) << ": " << argv[i] << endl;
  } // for

  cout << "#############################" << endl;

  execve(filename, argv+1, envp);
  perror("execve");
  return EXIT_FAILURE;

} // main
