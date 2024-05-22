/* this is IPC, based on POSIX; POSIX消息队列允许进程间异步交换数据。这需要包含头文件<mqueue.h>，并在编译时链接实时库rt
为了编译这个程序，你可能需要链接实时库，如使用g++的话，使用-lrt标志。*/
#include <fcntl.h> // for O_* constants, this is O not 0
#include <sys/stat.h> // for mode constants
#include <mqueue.h>
#include <iostream>
#include <cstring>
using namespace std;

int main() {
    mqd_t mq;  // message queue mq
    struct mq_attr attr;
    char buffer[1024 + 1];
    int msg, ret;

    // seeting mq attribute
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 1024;
    attr.mq_curmsgs = 0;

    // create mq
    mq = mq_open("/test_queue", O_CREAT | O_RDONLY, 0644, &attr); // if mq_open is unidentified, -lrt when gcc compile
    if(mq == (mqd_t)-1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    // receive message from mq
    memset(buffer, 0, sizeof(buffer));  // receive message and put in buffer (not read fragment of msg, 
    // so buffer should be large enough)
    ret = mq_receive(mq, buffer, 1024, NULL);
    if (ret == -1) {
        perror("mq_receive");
        mq_close(mq);
        mq_unlink("/test_queue");
        return 1;
    }

    cout << "Received: " << buffer << endl;

    // close and delete mq
    mq_close(mq);
    mq_unlink("/test_queue");

    return 0;
}

/*mqd_t
mqd_t是消息队列描述符的类型，用于标识一个打开的消息队列实例。这个类型的变量类似于文件描述符，是通过mq_open函数调用返回的，用于后续的所有消息队列操作，如mq_send、mq_receive、mq_close等。
通过mq_open创建或打开消息队列时，你会获得一个mqd_t类型的值，这个值在后续操作中作为消息队列的引用。
struct mq_attr
struct mq_attr是一个结构体，用于设置或获取消息队列的属性。它定义了消息队列的几个关键属性，如消息的最大数量、最大消息大小等。
这个结构体通常在使用mq_open创建消息队列时使用，以指定消息队列的属性。它也可以通过mq_getattr和mq_setattr函数来获取或修改已存在的消息队列的属性。*/

/* mqd_t mq_open(const char *name, int oflag, mode_t mode, struct mq_attr *attr);
name：这是消息队列的名称。按照约定，它应该以/开头，其后是队列的唯一标识符。在您的例子中，消息队列的名称是"/test_queue"。

oflag：这是打开消息队列时的标志，用来指定不同的打开或创建选项。O_CREAT标志表示如果指定名称的队列不存在，则创建它。O_RDONLY表示以只读方式打开队列。这些标志可以通过位或操作组合使用。

mode：当使用O_CREAT标志时，mode指定了新创建的消息队列的权限。它是一个八进制数，类似于在使用chmod命令或创建文件时指定的权限。0644表示拥有者具有读写权限，而组和其他用户具有读权限。

attr：这是一个指向mq_attr结构的指针，该结构指定了消息队列的属性，如最大消息长度、队列容量等。如果为NULL，则使用系统默认值。
*/