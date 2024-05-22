/*在UDP通信中，数据以消息（或称为数据报）的形式发送，不同于TCP，UDP不建立连接，
因此它是无连接的，并且不保证数据包的到达顺序、完整性或者到达本身。*/
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

int main() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;

    // create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // fil the server info
    servaddr.sin_family = AF_INET;  // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY; // receive data from any IP
    servaddr.sin_port = htons(8080); 

    // bind socket with server address
    if (bind(sockfd, (const struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    socklen_t len = sizeof(cliaddr);
    // receive data from client (cliaddr) first, then send hello message to client
    /*MSG_WAITALL是recvfrom函数的一个选项，它指示调用者希望函数阻塞直到请求的所有数据都被接收，或者直到发生错误或信号中断该调用为止*/
    int n = recvfrom(sockfd, (char*)buffer, 1024, MSG_WAITALL, (struct sockaddr*)&cliaddr, &len);
    buffer[n] = '\0';  // noting \0 standfor string, not \n
    cout << "client : " << buffer << endl;

    const char* message = "Hello from server";
    sendto(sockfd, message, strlen(message), MSG_CONFIRM, (const struct sockaddr*)&cliaddr, len);

    close(sockfd);
    return 0;
}