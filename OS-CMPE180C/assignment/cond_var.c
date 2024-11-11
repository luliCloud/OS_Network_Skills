#include <stdio.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <pthread.h>
#include <unistd.h>

// we must declare mutex and conditional var as the global var so that both thread can access.
// initialize the global mutex and cond var using system default setting
// https://web.stanford.edu/~ouster/cgi-bin/cs140-spring14/lecture.php?topic=locks
pthread_mutex_t mtx;
pthread_cond_t cond1, cond2;
int turn = 1; // track which thread is

void* t1_func(void* arg) {
    while (1) {
        pthread_mutex_lock(&mtx);
        while (turn != 1) {  // turn 1 is for thread 1
        /** conditaion var is to ensure the next executing thread is the one we want. e.g., cond1 corresponds
         * to thread1, cond2 for thread2. Once mutex released, all threads compted for mutex if no conditional
         * var. But if only cond1 signaled, then only thread will be awakened to obtain the mutex. there both 
         * signal mutex and cond1 ensure that thread1 can obtain the critical section execution
         */
            pthread_cond_wait(&cond1, &mtx); // auto release mtx and wait the cond1 to awake blocked thread 1
        }

        // first output from thread1. 
        printf("thread 1: ping thread 2\n");
        fflush(stdout); // ensure to output at the stdou immediately
        turn = 2;
        pthread_cond_signal(&cond2); // awake thread 2
        // pthread_mutex_unlock(&mtx); // release mtx

        while (turn != 1) {
            pthread_cond_wait(&cond1, &mtx); // block thread1 until cond1 awaken. lock released auto
        }

        // second output from thread 1
        // pthread_mutex_lock(&mtx);
        printf("thread 1: pong! thread 2 ping received\n");
        fflush(stdout);
        pthread_cond_signal(&cond2);
        pthread_mutex_unlock(&mtx);  // turn is not 2, enter next while loop in this func directly

        // sleep(1);
    }
    return NULL;
}

void* t2_func(void* arg) {
    while (1) {
        pthread_mutex_lock(&mtx); // must lock first. for both threads. will auto release upon wait
        while (turn != 2) {
            pthread_cond_wait(&cond2, &mtx);
        }

        // print the first msg in thread 2
        printf("thread 2: pong! thread 1 ping received\n");
        fflush(stdout);
        
        printf("thread 2: ping thread 1\n");
        fflush(stdout);
        turn = 1; // noting here, give back to 
        pthread_cond_signal(&cond1);
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

// deal with SIGINT, exit gracefully
void sigint_handler(int sig) {
    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cond1);
    pthread_cond_destroy(&cond2);
    exit(0);
}

int main() {
    signal(SIGINT, sigint_handler);

    // initialze mtx and cond var dynamically rather than statically
    if (pthread_mutex_init(&mtx, NULL)) {
        return 1;
    }

    if (pthread_cond_init(&cond1, NULL)) {
        return 1;
    }

    if (pthread_cond_init(&cond2, NULL)) {
        return 1;
    }

    pthread_t t1, t2;

    pthread_create(&t1, NULL, t1_func, NULL);
    pthread_create(&t2, NULL, t2_func, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}

/**Write a “C” program that creates two threads thread 1 and thread 2. 
 * 
 * Thread 1 prints exactly the following text in one and only one line (including a new line at the end of the
text): "thread 1: ping thread 2". 
Thread 1 then uses conditional variable functions to signal thread 2 and blocks on another conditional variable waiting to be signaled by
thread 2. 

Thread 2, upon being unblocked by thread 1 signal will print exactly the
following text: "thread 2: pong! thread 1 ping received" including a newline at the end.
Thread 2 will then proceed to print "thread 2: ping thread 1" and signal thread 1.

upon receiving this signal on its condition variable, thread 1 will print exactly: "thread 1: pong!
thread 2 ping received". 

From now on the sequence will repeat until the user of the
program issues Ctrl-C or send SIGINT to the process. 

Any deviation like adding extra lines or text will result in zero grade. 
Any unclean exit like using exit() or _exit() directly from the signal handler will likely cause no output to be flushed and hence result in zero
grade. 

Not placing a new line in each thread text will result in zero. 

Please be very careful in following instructions as your program will be graded by a script and there will be no
re-grade option if you did not follow the instructions. Use only pthreads condition
variables to synchronize the two threads. The strings above must be sent to stdout, not
doing so will result in zero grade.
 */