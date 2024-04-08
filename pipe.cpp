#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
#include <cstdlib>

using namespace std;

int main() {
    // arr of a pipe, connecting two process. generally pipefd[0] being read, [1] being written
    int pipefd[2]; 
    pid_t cpid; // child precess ID
    char buf; // cache for data stream

    // establish a pipe: generally size 65535 bytes. can resize. noting diff from buf size
    if (pipe(pipefd) == -1) {  // pipe() is for establish a pipe. fail return -1, success return 0
        cerr << "Pipe failed" << endl;
        return EXIT_FAILURE;
    }

    // create a child process，generally fork cid will be 0
    cpid = fork(); // fork() is to create a process, highly like to current process
    if (cpid == -1) {
        cerr << "Fork failed" << endl;
        return EXIT_FAILURE;
    }   
    // cpid is 11661, so enter write first
    if (cpid == 0) {
        close(pipefd[1]); // close write end

        // read from pipe (pipefd[0]). char indicate every time read 1 byte. stdout to standard output
        while (read(pipefd[0], &buf, 1) > 0) {
            write(STDOUT_FILENO, &buf, 1);  // STDOUT_FILENO is standard output(screa..)
        }
        write(STDOUT_FILENO, "\n", 1); // change line, improve infor readable
        close(pipefd[0]);
        _exit(EXIT_SUCCESS);
    } else {
        close(pipefd[0]); // close read end
        const char* msg = "Hello, world~\n";
        // write data to pipe
        write(pipefd[1],msg, strlen(msg));  // write msg into child fork
        close(pipefd[1]);
        wait(NULL); // wait child process exit
    }

    return EXIT_SUCCESS;
}

/**fork创建一个子进程是UNIX和类UNIX（如Linux）操作系统中一个常用的操作。当一个进程（我们通常称之为父进程）调用fork函数时，它会创建一个新的进程。这个新创建的进程被称为子进程。子进程是父进程的一个几乎完整的副本：它继承了父进程的数据空间、堆和栈的副本，但是执行序列是独立的。父进程和子进程从fork调用之后的地方开始分别执行，但是因为它们的地址空间是独立的，所以它们的执行路径可能会不同。

在fork成功后，有两个几乎相同的进程并行运行。为了区分这两个进程，fork函数在父进程中返回新创建的子进程的进程ID（一个正整数），而在子进程中返回0。如果出现错误，fork将在父进程中返回-1，并且不会创建子进程。

子进程可以通过调用exec系列函数来执行一个新的程序。这意味着子进程开始执行与父进程不同的代码，尽管它是从父进程复制过来的。这是在UNIX和类UNIX操作系统中创建新进程和执行新程序的标准方式。
在fork()调用之后，父进程和子进程都会从fork()的返回点继续执行，但是它们在各自的独立进程空间内执行，互不干扰。这就是为什么似乎同时有两个分支（父进程和子进程）在执行的原因。

在父进程中，fork()返回新创建的子进程的进程ID（一个正整数），所以cpid > 0的条件成立，父进程进入else部分的代码块。
在子进程中，fork()返回0，所以cpid == 0的条件成立，子进程进入if部分的代码块。
这意味着，尽管代码是以if-else结构组织的，父进程和子进程都会执行这段代码，但是它们会根据fork()返回的值进入不同的分支。子进程会执行if (cpid == 0)部分的代码，而父进程会执行else部分的代码。*/