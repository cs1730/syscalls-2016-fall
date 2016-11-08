
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

vector<char *> mk_cstrvec(vector<string> & strvec);
void dl_cstrvec(vector<char *> & cstrvec);
void nice_execve(vector<string> argv, vector<string> envp);

int main() {
  vector<string> argv { "cat", "pipe2.cpp" };
  vector<string> envp {};
  nice_execve(argv, envp);
  return EXIT_SUCCESS;
} // main

vector<char *> mk_cstrvec(vector<string> & strvec) {
  vector<char *> cstrvec;
  for (unsigned int i = 0; i < strvec.size(); ++i) {
    cstrvec.push_back(new char [strvec.at(i).size() + 1]);
    strcpy(cstrvec.at(i), strvec.at(i).c_str());
  } // for
  cstrvec.push_back(nullptr);
  return cstrvec;
} // mk_cstrvec

void dl_cstrvec(vector<char *> & cstrvec) {
  for (unsigned int i = 0; i < cstrvec.size(); ++i) {
    delete[] cstrvec.at(i);
  } // for
} // dl_cstrvec

void nice_execve(vector<string> argv, vector<string> envp) {
    vector<char *> cargv = mk_cstrvec(argv);
    vector<char *> cenvp = mk_cstrvec(envp);
    execve(cargv.at(0), &cargv.at(0), &cenvp.at(0));
    perror("execve");
    dl_cstrvec(cargv);
    dl_cstrvec(cenvp);
    exit(EXIT_FAILURE);
} // nice_exec

