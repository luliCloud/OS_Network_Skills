/* 服务器端创建一个套接字，绑定到一个地址和端口上，然后监听来自客户端的连接。
一旦接受了连接，它就会读取客户端发送的数据，并将相同的数据回发给客户端。 
注意，client-server mode using socket is also used by TCP/IP */
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h> // for sockaddr_in 
#include <unistd.h> 
#include <string.h>
using namespace std;

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address; // store internet address
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    const char* hello = "Hello from server";

    // create socket, this server_fd from socket will be bound to server ip and port
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // bind socket to port: port, 用于识别特别服务或者进程
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080); // 8080 the port num to be used
    // bind socket with server address and port
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // listern, maximum 3 request. reject if more than 3 request
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // accept connet
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accpet");
        exit(EXIT_FAILURE);
    }

    // read data from client
    read(new_socket, buffer, 1024);
    cout << "Message from client: " << buffer << endl;

    // send data to client
    send(new_socket, hello, strlen(hello), 0);
    cout << "Hello message send\n";

    close(new_socket);
    close(server_fd);

    return 0;
}
/*socket(AF_INET, SOCK_STREAM, 0)
socket函数用于创建一个新的套接字，并返回一个套接字描述符。这个描述符是一个整数值，用于在后续的系统调用中标识这个套接字。
AF_INET参数指定地址族为IPv4 Internet protocols，用于IPv4网络通信。
SOCK_STREAM参数指定套接字类型为流套接字，用于TCP连接。
最后一个参数0表示使用默认的协议（对于TCP，即IPPROTO_TCP）。*/

/*套接字的工作流程（以TCP为例）：
服务器创建套接字：服务器通过调用socket()函数创建一个套接字，并得到一个套接字描述符（一个整数值，用于标识这个套接字）。
绑定地址和端口：服务器使用bind()函数将套接字绑定到一个具体的IP地址和端口号上。这样，客户端就知道如何连接到这个服务器。
监听连接请求：服务器通过调用listen()函数使套接字进入监听状态，准备接受客户端的连接请求。
接受连接：当客户端尝试连接到服务器时，服务器通过调用accept()函数接受连接请求，并得到一个新的套接字描述符，用于与这个特定客户端的通信。
数据交换：一旦连接建立，服务器和客户端就可以通过send()和recv()（或类似的）函数来交换数据。
关闭套接字：通信完成后，双方通过调用close()函数关闭套接字，结束通信。*/

/* htons：htons是“Host TO Network Short”的缩写，它是一个函数，用于将一个短整型数值（16位，如端口号）从主机字节顺序转换为网络字节顺序。
这个转换是必要的，因为不同的计算机体系结构可能有不同的字节顺序（即端序问题）。大多数网络协议，包括TCP/IP，
使用大端序作为标准的网络字节顺序。*/

/*在套接字编程中，accept函数是服务器用来接受客户端的连接请求的。一旦listen函数使套接字进入监听状态，服务器就可以通过调用accept来接受进入的连接请求。
这个函数调用会阻塞进程，直到客户端的连接请求到达，除非套接字被配置为非阻塞模式。
new_socket：这是一个整数值，表示新的套接字描述符。如果accept成功，这个描述符用于与请求连接的客户端进行通信。它是与客户端的唯一连接关联的，
而server_fd则继续在监听其他的连接请求。
*/