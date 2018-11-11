#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>

#define PORT   8888  /*监听端口地址*/
void process_conn_client(int sock);

void *sig_pipe(int sign)
{
    printf("Catch a SIGPIPE signal \n");
}
void *sig_int(int sign)
{
    printf("Catch a SIGINT signal \n");
}

int main(int argc, char *argv[])
{
    int err = -1;
    int sfd = -1;
    struct sockaddr_in server_addr;

    signal(SIGPIPE, sig_pipe);
    signal(SIGINT, sig_int);
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sfd == -1){
        perror("client create socket");
        return -1;
    }
    /*设置服务器地址*/
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    /*将用户输入的字符串类型的IP地址转为整数*/
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);
    /*连接服务器*/
    err = connect(sfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(err == -1){
        perror("client connect");
        return -1;
    }
    process_conn_client(sfd);
    close(sfd);

    return 0;
}
void process_conn_client(int sock)
{
    ssize_t size = -1;
    char buffer[1024] = {0};
    while((size = read(0, buffer, sizeof(buffer))) > 0){
        write(sock, buffer, size);
        size = read(sock, buffer, sizeof(buffer));
        write(1, buffer, size);
        memset(buffer, 0x0, sizeof(buffer));
    }
    printf("client process end\n");
}
