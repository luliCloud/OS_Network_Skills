/* 客户端连接到服务器的地址和端口，发送一个消息，然后读取并打印服务器的回复。*/
/* 我们使用的localhost，所以实际上server也是我们本机。而在实际应用中，我们要将ip地址和端口设成真正主机的ip和端口
for inet_pton and serv_addr.sin_port*/
/* instruction for testing: compile socket files respectively
g++ socketServer.cpp -o server
g++ socketClient.cpp -o client
./server  // running this first
./client
*/
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
using namespace std;

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    const char* hello = "Hello from client";
    char buffer[1024] = {0};

    // create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        cout << "socket creation error" << endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    // convert IP4 addree from string to binary
    /* noting here use localhost address, in real application, we will used the address of server instead of local
    we use the local to mimic the server, i.e. client and server are both our end*/
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) { 
        cout << "Invalid address / Address not supported" << endl;
        return -1;
    }

    // connet
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) {
        cout << "Connection failed" << endl;
        return -1;
    }

    // send data
    send(sock, hello, strlen(hello), 0);
    cout << "Hello message sent" << endl;

    // read data from server
    read(sock, buffer, 1024);
    cout << "Message from server: " << buffer << endl;

    close(sock);
}