/* please use this one with messageQueue_receiver.cpp together
this is IPC, based on POSIX; POSIX消息队列允许进程间异步交换数据。这需要包含头文件<mqueue.h>，并在编译时链接实时库rt
为了编译这个程序，你可能需要链接实时库，如使用g++的话，使用-lrt标志。*/
#include <fcntl.h> // for O_* constants, this is O not 0
#include <sys/stat.h> // for mode constants
#include <mqueue.h>
#include <iostream>
#include <cstring>
using namespace std;

int main() {
    mqd_t mq = mq_open("/test_queue", O_CREAT | O_WRONLY, 0644, NULL);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    const char* message = "Hello, World!";
    if (mq_send(mq, message, strlen(message) + 1, 0) == -1) {
        perror("mq_send");
        exit(EXIT_FAILURE);
    }

    std::cout << "Message sent: " << message << std::endl;

    mq_close(mq);  // ensure don't close during sending

    return 0;
}

/* 
g++ -o receiver receiver.cpp // don't add -lrt, otherwise failed
g++ -o sender sender.cpp // don't add -lrt

./receiver
// open a new bash
./sender
两个程序会同市运行。有两个线程
当发送程序执行并发送消息后，接收程序应该会从阻塞状态解除，显示接收到的消息，并正常退出。
(base) lu@lu-t3610:~/greenpear/OSlearn$ ./sender
Message sent: Hello, World!
(base) lu@lu-t3610:~/greenpear/OSlearn$ ./receiver
Received: Hello, World!
 */