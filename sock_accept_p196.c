#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>

#define BACKLOG 10
#define MY_PORT 5566 

int main(int argc, char *argv[])
{
    int sockfd = -1;
    int client_fd = -1;
    struct sockaddr_in my_addr;
    struct sockaddr_in client_addr; 
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MY_PORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;//inet_addr("192.168.0.102");//ANY_ADDR;
    bzero(&(my_addr.sin_zero), sizeof(my_addr.sin_zero));

    if(bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("bind");
        return -1;
    }
    if(listen(sockfd, BACKLOG) == -1)
    {
        perror("listen");
        return -1;
    }
    printf("server wait accept\n");
    int addr_length = sizeof(struct sockaddr_in);
    client_fd = accept(sockfd, &client_addr, &addr_length);
    if(client_fd == -1)
    {
        perror("accept");
        return -1;
    }
    printf("client_fd = %d\n", client_fd);
    close(client_fd);
    close(socket);

    return 0;
}


