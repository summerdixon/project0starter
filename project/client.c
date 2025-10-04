#include <arpa/inet.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char** argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: client <hostname> <port> \n");
        exit(1);
    }

    // Only supports localhost as a hostname, but that's all we'll test on
    const char* addr =
        strcmp(argv[1], "localhost") == 0 ? "127.0.0.1" : argv[1];
    int port = atoi(argv[2]);

    // TODO: Create socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // TODO: Set stdin and socket nonblocking
    int flags = fcntl(sockfd, F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(sockfd, F_SETFL, flags);

    flags = fcntl(0, F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(0, F_SETFL, flags);

    // TODO: Construct server address
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(addr);
    
    serveraddr.sin_port = htons(port);

    int BUF_SIZE = 1024;
    char server_buf[BUF_SIZE];
    socklen_t serversize = sizeof(struct sockaddr_in);

    // Listen loop
    while (1) {
        // TODO: Receive from socket
        int bytes_recvd = recvfrom(sockfd, server_buf, BUF_SIZE, 
                           0, (struct sockaddr*) &serveraddr, 
                           &serversize);
        // TODO: If data, write to stdout
        if (bytes_recvd > 0)
        {
            write(1, server_buf, bytes_recvd);
        }
        else if (bytes_recvd < 0)
        {
            if (errno != EAGAIN && errno != EWOULDBLOCK) break;
        }
        // TODO: Read from stdin
        int bytes_read = read(0, server_buf, BUF_SIZE);
        // TODO: If data, send to socket
        if (bytes_read > 0) 
        {
            sendto(sockfd, server_buf, bytes_read,
                    0, (struct sockaddr*) &serveraddr, 
                    sizeof(serveraddr));
        }
        else if (bytes_read < 0)
        {
            if (errno != EAGAIN && errno != EWOULDBLOCK) break;
        }
    }

    close(sockfd);

    return 0;
}