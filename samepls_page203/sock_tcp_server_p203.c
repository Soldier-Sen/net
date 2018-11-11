#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <linux/in.h>

#define BACKLOG  10     /*监听队列长度*/
#define PORT     8888   /*监听端口地址*/

void process_conn_server(int sockfd);

int main(int argc, char *argv[])
{
    int ss, sc;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int err = -1;
    pid_t pid;

    /*建立一个AF_INET域的流式套接字*/
    ss = socket(AF_INET, SOCK_STREAM, 0);
    if(ss == -1){
        perror("create socket");
        return -1;
    }
    /*设置服务器地址*/
    bzero(&server_addr, sizeof(server_addr));    /*清零*/
    server_addr.sin_family = AF_INET;            /*协议族*/
    server_addr.sin_port = htons(PORT);          /*服务器端口*/
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); /*本地地址*/
    /*绑定地址结构到套接字描述符*/
    err = bind(ss, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(err == -1){
        perror("server bind");
        return -1;
    }
    /*设置监听端口*/
    err = listen(ss, BACKLOG);
    if(err == -1){
        perror("server listen");
        return -1;
    }
    /*主循环过程*/
    while(1){
        unsigned int addr_len = sizeof(struct sockaddr);
        sc = accept(ss, (struct sockaddr *)&client_addr, &addr_len);
        if(sc == -1){
            continue;
        }
        pid = fork();
        if(pid == 0){
            close(ss);
            process_conn_server(sc);
        }
        else{
            close(sc);
        }
    }
    

    return 0;
}
/*服务器对客户端的处理*/
void process_conn_server(int sockfd)
{
    ssize_t size = 0;
    char buffer[1024] = {0};
    while((size = read(sockfd, buffer, sizeof(buffer))) > 0){
        printf("server: receive %s\n", buffer);
        sprintf(buffer, "%ld bytes altogether\n", size);
        write(sockfd, buffer, strlen(buffer) + 1);
        memset(buffer, 0x0, sizeof(buffer));
    }
    printf("server process client %d request end\n", sockfd);
}
