#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h> // for macro of WIFEXITED
#include <unistd.h>

int main() {
    pid_t pid;

    /* fork a child process */
    pid = fork();

    if (pid < 0) { /* error occurred */
        fprintf(stderr, "Fork Failed");
        return 1; // remember return this
    } else if (pid == 0) { /* child process*/
        execlp("/bin/ls", "ls", NULL); 
        exit(1); // exit with status 1, parent will receive 1
        /* overlays its address space with the UNIX command /bin/ls 
        (used to get a directory listing) using the execlp()
        system call (execlp() is a version of the exec() system call). */
        /* execlp() 是什么？
execlp() 是一种 exec 系列的函数，用来将当前进程的代码和数据替换为另一个程序的代码和数据。exec 系列的函数家族包含多个函数，如 execl, execp, execvp 等，它们的主要作用是执行指定的程序。

execlp() 函数的具体语法：

int execlp(const char *file, const char *arg, ..., NULL);
参数：
file: 要执行的程序的名称或路径（execlp 可以使用路径或直接使用命令名）。

例子中的 /bin/ls 指定了要执行的程序是 ls，它位于 /bin 目录下。
arg: 程序的命令行参数。第一个参数通常是程序自己的名字（习惯上这样做），后面的参数是你要传递给程序的参数。它以 NULL 结尾，表示参数列表结束。

在这个例子中，"ls" 作为第一个参数，表示程序的名称。这里的 ls 就是传递给程序的命令名。
NULL: 参数列表必须以 NULL 结尾，用来告诉 execlp 这个参数列表已经结束。

*/
    } else if (pid > 0) { /* parent process, obtain child pid*/
        int status;
        wait(&status); /* parent process wait child process to finish */
        /** parent obtain exit status of child */
        if (WIFEXITED(status)) {
            printf("Child process exit normally, with exit status %d\n", 
            WIFEXITED(status));
        } else {
            printf("child process exit abnormally\n");
        }

        /* in other cases, parent can continue to execute other functions
        or open new children process if not write wait() 
        or can wait(pid), to wait for specific children process terminated */
    }
    return 0;
}