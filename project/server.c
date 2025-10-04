#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: server <port>\n");
        exit(1);
    }

    int port = atoi(argv[1]);

    // TODO: Create socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // TODO: Set stdin and socket nonblocking
    int flags = fcntl(sockfd, F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(sockfd, F_SETFL, flags);

    // TODO: Construct server address
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int PORT = 8080;
    servaddr.sin_port = htons(PORT);

    // TODO: Bind address to socket
    int did_bind = bind(sockfd, (struct sockaddr*) &servaddr, 
                    sizeof(servaddr));
    if (did_bind < 0) return errno;

    // TODO: Create sockaddr_in and socklen_t buffers to store client address
    int BUF_SIZE = 1024;
    char client_buf[BUF_SIZE];
    struct sockaddr_in clientaddr = {0}; 
    socklen_t clientsize = sizeof(clientaddr);

    int client_connected = 0;

    // Listen loop
    while (1) {
        // TODO: Receive from socket
        int bytes_recvd = recvfrom(sockfd, client_buf, BUF_SIZE, 
                           0, (struct sockaddr*) &clientaddr, 
                           &clientsize);
        // TODO: If no data and client not connected, continue
        if (bytes_recvd <= 0) continue;
        // TODO: If data, client is connected and write to stdout
        // TODO: Read from stdin
        // TODO: If data, send to socket

        if (bytes_recvd < 0) return errno;
    }

    return 0;
}