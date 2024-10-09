#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

void signal_handler(int sig) {
    // using waitpid to reap all child zombie process
    pid_t pid;
    int zombia_cleaned = 0;
    int olderrno = errno; //signal() will not reset the errno, we must manually set later

    while ((pid = waitpid(-1, NULL, WNOHANG)) > 0) { // pid == 0 skip iteration, indicate no zombia
        //  cleaning one child process
        // -1: wait for any child process. NULL indicate not caring exit process of child
        // WNOHANG indicate if no child process exit, waitpid() return immediately. non-blocking status
        // 0: one child will block the parent process until if successfully exit
        printf("Reap zombie process %d\n", pid);
        zombia_cleaned++;
    }

    // when every child exit will send a signal. ECHILD indicate all child exit and cleaned
    if (errno == ECHILD) { // ECHILD indicate all children have been cleaned up
        printf("Total of %d zombie processes cleaned. All zombie processes have been reaped.\n", 
        zombia_cleaned);
    } else if (errno != ECHILD) {
        fprintf(stderr, "waitpid failed\n");
        exit(1);
    }
    errno = olderrno;
}

int main(int argc, char** argv) {
    if (argc != 3 || strcmp(argv[1], "-n") != 0) {
        fprintf(stderr, "Please input as the format: %s -n <num of zombies>\n", argv[0]);
        exit(1); // why does we use exit instead of return
    }

    int zombie_num = atoi(argv[2]);
    if (zombie_num <= 0) {
        fprintf(stderr, "please input a number greater than zero as the zombie's count.\n");
        exit(1);
    }

    int i;
    for (i = 0; i < zombie_num; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            exit(0);  // make the child to be a zombie
        } else if (pid < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        } 
        // for parent process, enter next iteration
    }

    // using signal() to handle the SIGCONT singal
    if (signal(SIGCONT, signal_handler) == SIG_ERR) { // SIG_ERR is false return type of signal
    // indicate signal does not handle signal correctly
        fprintf(stderr, "Cannot handle signal correctly\n");
        exit(1);
    }
    pause(); // waiting for SIGCONT
    return 0;
}

/**
 * testing
 * bash 1: ./a.out -n 3
 * bash 2: Z+ indicate zombie process. 113427 should be parent process
 * ps aux | grep a.out
gcp2024+  114165  0.0  0.0   2364   512 pts/1    S+   06:55   0:00 ./a.out -n 3
gcp2024+  114166  0.0  0.0      0     0 pts/1    Z+   06:55   0:00 [a.out] <defunct>
gcp2024+  114167  0.0  0.0      0     0 pts/1    Z+   06:55   0:00 [a.out] <defunct>
gcp2024+  114168  0.0  0.0      0     0 pts/1    Z+   06:55   0:00 [a.out] <defunct>
gcp2024+  114231  0.0  0.0   8168   724 pts/2    S+   06:55   0:00 grep --color=auto a.out

bash 2: kill -SIGCONT 114165
bash 1 output:
Reap zombie process 114166
Reap zombie process 114167
Reap zombie process 114168
Total of 3 zombie processes cleaned. All zombie processes have been reaped.
 */