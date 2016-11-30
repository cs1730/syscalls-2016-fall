
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "nope.h"

using namespace std;

void close_pipe(int pipefd [2]);

int main(const int argc, const char * argv []) {

  int pipefd [2][2];
  int pid;

  // create first pipe
  if (pipe(pipefd[0]) == -1) {
    nope_out("pipe");
  } // if

  // create first child
  if ((pid = fork()) == -1) {
    nope_out("fork");
  } else if (pid == 0) {

    if (dup2(pipefd[0][1], STDOUT_FILENO) == -1) {
      nope_out("dup2");
    } // if

    close_pipe(pipefd[0]);

    char ** args = new char * [3];
    args[0] = strdup("cat");
    args[1] = strdup("pipe.cpp");
    args[2] = nullptr;

    execvp(args[0], args);
    
    perror("execvp");
    for (int i = 0; i < 3; ++i) free(args[i]);
    delete[] args;
    exit(EXIT_FAILURE);

  } // if

  // create second pipe
  if (pipe(pipefd[1]) == -1) {
    nope_out("pipe");
  } // if

  // create second child
  if ((pid = fork()) == -1) {
    nope_out("fork");
  } else if (pid == 0) {

    if (dup2(pipefd[0][0], STDIN_FILENO) == -1) {
      nope_out("dup2");
    } // if

    if (dup2(pipefd[1][1], STDOUT_FILENO) == -1) {
      nope_out("dup2");
    } // if

    close_pipe(pipefd[0]);
    close_pipe(pipefd[1]);

    char ** args = new char * [3];
    args[0] = strdup("grep");
    args[1] = strdup("//");
    args[2] = nullptr;

    execvp(args[0], args);
    
    perror("execvp");
    for (int i = 0; i < 2; ++i) free(args[i]);
    delete[] args;
    exit(EXIT_FAILURE);

  } // if

  // close first pipe
  close_pipe(pipefd[0]);

  // create third child
  if ((pid = fork()) == -1) {
    nope_out("fork");
  } else if (pid == 0) {

    if (dup2(pipefd[1][0], STDIN_FILENO) == -1) {
      nope_out("dup2");
    } // if

    close_pipe(pipefd[1]);

    char ** args = new char * [2];
    args[0] = strdup("less");
    args[1] = nullptr;

    execvp(args[0], args);
    
    perror("execvp");
    for (int i = 0; i < 2; ++i) free(args[i]);
    delete[] args;
    exit(EXIT_FAILURE);

  } // if

  // close second pipe
  close_pipe(pipefd[1]);

  // wait on last child
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


