#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>

#define DEST_IP  "192.168.0.102"
#define DEST_PORT 5566

int main(int argc, char *argv[])
{
    int ret = -1;
    int sockfd = -1;
    struct sockaddr_in server;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
    {
        perror("socket");
        return -1;
    }
    server.sin_family = AF_INET;
    server.sin_port = htons(DEST_PORT);
    server.sin_addr.s_addr = inet_addr(DEST_IP);//htonl(DEST_IP);
    bzero(&(server.sin_zero), sizeof(server.sin_zero));
    printf("socket connect\n");
    ret = connect(sockfd, (struct sockaddr *)&server, sizeof(struct sockaddr));
    if(ret == -1)
    {
        perror("connect");
        return -1;
    }
    printf("client finsh\n");
    close(sockfd);
    return 0;
}
