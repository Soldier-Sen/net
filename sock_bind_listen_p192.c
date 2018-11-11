#include <stdio.h>
#include <sys/types.h>
#include <sys/socks.h>

#define MY_PORT 3490

int main(int argc, char *argv[])
{
    int sockfd = -1;
    struct sockaddr_in my_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1){
        perror("socket");
        return -1;
    } 
    my_addr.sin_family = AF_INET;
    my_addr_sin_port = htons(MY_PORT);
    my_addr.sin_addr.s_addr = inet_addr("192.168.0.102");
    bzero(&(my_addr.sin_zero), sizeof(my_addr.sin_aero));

    if(bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("bind");
        return -1;
    }
    if(listen(sockfd, 5) == -1)
    {
        perror("listen");
        return -1;
    }
    close(fd);
    return 0;
}


