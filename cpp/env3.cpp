
/*!
 *    _________               /\  
 *   /   _____/__ ____________)/  
 *   \_____  \|  |  \____ \__  \  
 *   /        \  |  /  |_> > __ \_
 *  /_______  /____/|   __(____  /
 *          \/      |__|       \/  
 *
 *  \author    Michael E. Cotterell <mepcott@uga.edu>
 *  \date      2016-10-30
 */

#include <ios>
#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

int main(const int argc, const char * argv [], const char * envp []) {
  
  // turn off buffering for cout
  cout.setf(std::ios::unitbuf);

  for (int i = 0; envp[i] != nullptr; ++i) {
    cout << envp[i] << endl;
  } // for

  return EXIT_SUCCESS;
  
} // main


