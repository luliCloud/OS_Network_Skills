#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

// Q: how many process has been generated during this program

int main() {
    pid_t pid;
    pid = fork();

    if (fork()) {
        fork();
    }

    if (pid) {
        fork();
    }

    return 0;
}
/** answer should be 6
 * fork() -> 2: parent and child
 * if (fork()), parent->fork() (return PID >0) child 2+1. 
 * Child->fork()(return PID = 0), child 3 + 1. child process fork() always return 0
 * only parent(if fork enter if body), fork again. 4 + 1
 * if(pid), only parent enter, fork, 5 + 1
 * 
 * 6
 */