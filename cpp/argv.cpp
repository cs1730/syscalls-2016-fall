
#include <iostream>

using namespace std;

int main(const int argc, const char * argv []) {
  for (int i = 0; i < argc; ++i) {
    cout << (argv[i]+1) << endl;
  } // for
  return 0;
} // main
