#include <stdio.h>
#include <stdlib.h>  // exit()
#include <sys/wait.h> // for wait() system call
#include <sys/types.h> // pid_t
#include <unistd.h>  // for getpid(), fork(), pause()
#include <signal.h>  // for SIGINT

void signal_handler(int sig) {
    exit(5);
}

int main() {
    pid_t pid = fork();

    if (pid == 0) {  // child process
        printf("The child pid is %d\n", getpid()); // use %d for int

        // handle a SIGNIT (Ctrl + C)
        signal(SIGINT, signal_handler);
        pause();  // wait for a signal. should not put pause before. otherwise
        // not even enter signal
    } else if (pid > 0) {  // parent process
        int status;
        waitpid(pid, &status, 0);  
        // receiving status here. 0 is options position. 0 is by default 

        // WIFEXITED (macro, short for wait if exited) 
        // is to interpret the status back to exit(status). Otherwise it is 
        // shown as 1280, an encode to include whether exit normally, which signal causing termination
        // and if child process to be paused, relevant info.
        if (WIFEXITED(status)) { // ensure the child process exit correctly
            printf("The children process pid %d exit normally with exit status %d\n", 
            pid, WEXITSTATUS(status));
        } else {
            return -1;
        }
    } else if (pid == -1) {  // error. not fork() success
        fprintf(stderr, "The fork process failed/n");
        return -1;
    }
    return 0;
}
    
    /** For program testing:
     * bash 1 : execute ./a.out
     * bash 2 : copy the pid of child and use kill with SIGINT to kill child process
     * kill -SIGINT [child_pid]
     */