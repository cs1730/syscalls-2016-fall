
#include <array>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

void close_pipe(int pipefd [2]);
vector<char *> mk_cstrvec(vector<string> & strvec);
void dl_cstrvec(vector<char *> & cstrvec);
void nice_exec(vector<string> args);

int main(const int argc, const char * argv []) {

  int pid;
  //  int job_out;

  //  const char * const days [] = { "mon", "tue", "wed", "thur","fri", "sat", "sun", nullptr };

  //  if ((job_out = open("pipe3.txt", O_CREAT | O_TRUNC, 0644)) == -1) {
  //	perror("open");
  //	exit(EXIT_FAILURE);
  //  } // if

  vector<vector<string>> commands {
    { "cat", "pipe3.cpp" },
    { "grep", "perror" },
    { "less" }
  };

  vector<array<int, 2>> pipes(commands.size() - 1);

  for (unsigned int i = 0; i < commands.size(); ++i) {

    if (i != commands.size() - 1) {
      if (pipe(pipes.at(i).data()) == -1) {
	perror("pipe");
	exit(EXIT_FAILURE);
      } // if
    } // if

    if ((pid = fork()) == -1) {
      perror("fork");
      exit(EXIT_FAILURE);
    } else if (pid == 0) {

      if (i != 0) {
	if (dup2(pipes.at(i)[0], STDIN_FILENO) == -1) {
	  perror("dup2");
	  exit(EXIT_FAILURE);
	} // if
	close_pipe(pipes.at(i).data());
      } // if

      if (i != commands.size() - 1) {
	if (dup2(pipes.at(i-1)[1], STDOUT_FILENO) == -1) {
	  perror("dup2");
	  exit(EXIT_FAILURE);
	} // if
	close_pipe(pipes.at(i-1).data());
      } /* else {
	if (dup2(job_out, STDOUT_FILENO) == -1) {
	  perror("dup2");
	  exit(EXIT_FAILURE);
	} // if
      } // if
	*/

      nice_exec(commands.at(i));

    } // if

  } // for

  
  //  close_pipe(pipefd);

  waitpid(pid, nullptr, 0);
  return EXIT_SUCCESS;

} // main

void close_pipe(int pipefd [2]) {
  if (close(pipefd[0]) == -1) {
    perror("close");
    exit(EXIT_FAILURE);
  } // if
  if (close(pipefd[1]) == -1) {
    perror("close");
    exit(EXIT_FAILURE);
  } // if
} // close_pipe

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

void nice_exec(vector<string> strargs) {
    vector<char *> cstrargs = mk_cstrvec(strargs);
    execvp(cstrargs.at(0), &cstrargs.at(0));
    perror("execvp");
    dl_cstrvec(cstrargs);
    exit(EXIT_FAILURE);
} // nice_exec

