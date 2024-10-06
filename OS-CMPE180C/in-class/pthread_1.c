#include <stdio.h>
#include <stdlib.h> // for atoi
#include <pthread.h>

int sum; // shared by threads
void *runner(void *param); // thread call this function. prototype

int main(int argc, char** argv) {
    pthread_t tid; // thread id
    pthread_attr_t attr; 
    /** 这是声明了一个类型为 pthread_attr_t 的变量 attr。
pthread_attr_t 是 POSIX 线程库中用来保存线程属性的类型。
线程属性允许你自定义线程的行为，比如设置线程的栈大小、调度策略、优先级、以及线程是可连接（joinable）还是分离（detached）的。
     * 为什么要初始化
     这行代码的作用是初始化线程属性对象 attr 并赋予默认值。调用完这个函数后，attr 变量就已经准备好，并带有默认的线程属性设置。
     避免后续因为没有初始化某些值出现不可预测的行为
     */

    if (argc != 2) {
        fprintf(stderr, "usage: a.out <integer value>\n");  
        // tell the user how to input right arg. 2nd arg should be a <integer value>
        return -1;
    }
    if (atoi(argv[1]) < 0) {
        fprintf(stderr, "%d must be >= 0\n", atoi(argv[1]));
        return -1;
    }

    /* get the default attr */
    pthread_attr_init(&attr);
    /* create the thread */
    pthread_create(&tid, &attr, runner, argv[1]);
    /* wait for the thread to exit, similar to wair() */
    pthread_join(tid, NULL); // if we change NULL to a &num then we can get the exit status of child thread

    printf("sum = %d\n", sum);
    return 0;
}

/* void * is the return type of runner, not the runner itself is a pointer to func*/
void *runner(void *param) {
    int i, upper = atoi(param);
    for (i = 0; i <= upper; i++) {
        sum += i;
    }
    pthread_exit(0);
}
// need to explicitly telling compiler that pthread lib is used
// gcc -pthread pthread_1.c -o pthread_1
