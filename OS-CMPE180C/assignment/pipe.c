#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h> 
#define READEND 0
#define WRITEEND 1
#define SIZE 128

int main() {
    int pipePtoC[2], pipeCtoP[2];
    pid_t pid;
    char buffer[SIZE];

    // create ordinary pipe, one from parent to child, and one from child to parent
    if (pipe(pipePtoC) == -1 || pipe(pipeCtoP) == -1) {
        fprintf(stderr,"Pipe failed");
        return 1;
    }

    pid = fork(); // create a child process

    if (pid == -1) {
        fprintf(stderr,"Fork failed");
        return 1;
    } else if (pid > 0) { // parent
        close(pipePtoC[READEND]);
        close(pipeCtoP[WRITEEND]); // forbid child to write. parent need to write first

        // write message
        snprintf(buffer, sizeof(buffer), "I am your daddy! and my name is %d\n", getpid());
        write(pipePtoC[1], buffer, strlen(buffer) + 1); // end with '\0'

        // read message from child
        read(pipeCtoP[READEND], buffer, sizeof(buffer));
        printf("Message from children: %s", buffer); // children already sent message with \n

        close(pipePtoC[WRITEEND]);
        close(pipeCtoP[READEND]);

        wait(NULL); // wait for child to exit first
    } else if (pid == 0) {  // child process
        close(pipeCtoP[READEND]);
        close(pipePtoC[WRITEEND]);

        // read message from parent
        read(pipePtoC[READEND], buffer, sizeof(buffer));
        printf("Message from parent: %s", buffer);

        // write message to parent
        snprintf(buffer, sizeof(buffer), "Daddy, my name is %d\n", getpid());
        write(pipeCtoP[WRITEEND], buffer, sizeof(buffer) + 1);

        close(pipePtoC[READEND]);
        close(pipeCtoP[WRITEEND]);
    }
    return 0;
}