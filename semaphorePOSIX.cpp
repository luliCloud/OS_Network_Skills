/* this demo is for IPC, process */
#include <fcntl.h> // define 0_* constant, belong to POSIX
#include <sys/stat.h>  // define mode constant, this .h belonge to POSIX
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main() {
    /*尝试打开一个名为/my_ipc_semaphore的命名信号量。如果这个信号量不存在，则用权限模式0644创建它。
    将新创建的信号量的初始值设置为1，这通常用于互斥访问资源。*/
    sem_t* sem = sem_open("/my_ipc_semaphore", O_CREAT, 0644, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    // try decrease semaphore, enter critical section: shared memory
    if (sem_wait(sem) == -1) {  // if sem > 0, sem_wait-- sem, if sem==0, 
    // the one called sem_wait will be suspend (blocked). but sem not--
        perror("sem_wait");
        exit(EXIT_FAILURE);
    }
    
    // critial section, execute work of this process

    // close semaphore, i.e. release
    if (sem_post(sem) == -1) {
        perror("sem_clase");
        exit(EXIT_FAILURE);
    }

    // delete semaphore
    if (sem_unlink("/my_ipc_semaphore") == -1) {
        perror("sem_unlink");
        exit(EXIT_FAILURE);
    }
    return 0;
}