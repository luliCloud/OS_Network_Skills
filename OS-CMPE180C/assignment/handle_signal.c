#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

// global variable to change during the SIGINT
int debug;  // 0 for toggle off (no printing) and 1 for toggle on

// SIGINT handler (toggle debug mode on and off)
void signal_handlerINT(int sig) { // sig is the signal that handler catching. for multiple sig handeling
    if (debug == 0) {
        debug = 1; // turn 
    } else if (debug == 1) {
        debug = 0;
    }
}

// SIGSR1 handler (gracefully terminate the program)
void signal_handlerUSR1(int sig) {
    printf("Receiving signal SIGUSR1 and exit the program\n");
    exit(0);
}

/** the logic is whether we repress the SIGINT, it only affect the value of debug, and whether
     * toggle mode is on or off. 
     * but the while loop keep going, iteration keep increasing for every cycle sleep for 1 second
     * and the print mode only show those iterasion with print on mode
     * while is true until meet SIGSR1 mode
     */

int main() {
    debug = 0; // initialize debug as 0, which is toggle off status
    int iteration = 0; // record how many iterator have so far. 
    
    if (signal(SIGINT, signal_handlerINT)) {
        fprintf(stderr, "Cannot handle SIGINT correctly\n");
        exit(1);
    }
    if (signal(SIGUSR1, signal_handlerUSR1)) {
        fprintf(stderr, "Cannot handle SIGSR1 correctly\n");
        exit(1);
    }

    while (1) { // c only have zero and non-zero and false and true
        if (debug == 1) {
            printf("Currently at iteraion %d\n", iteration);
        }
        iteration++;
        sleep(1); // every iteration sleep for 1 second
    }
    return 0;
}

/**
ps aux | grep a.out
gcp2024+  248531  0.0  0.0   2364   576 pts/0    S+   04:54   0:00 ./a.out
gcp2024+  248588  0.0  0.0   8168   656 pts/1    S+   04:55   0:00 grep --color=auto a.out

kill -SIGINT 248531 // toggle on
kill -SIGINT 248331 // toggle off, stop printing 
kill -SIGUSR1 248531 // noting is USR1 not SR1

Currently at iteraion 12
Currently at iteraion 13
Currently at iteraion 14
Currently at iteraion 19
Currently at iteraion 20
Currently at iteraion 21
Currently at iteraion 22
Receiving signal SIGUSR1 and exit the program
 */