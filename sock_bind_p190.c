#include <stdio.h>
#include <sys/types.h>
#include <sys/socks.h>

#define MY_SOCKET_PATH    "/home/hhs/study/net/sock_path"

int main(int argc, char *argv[])
{
    int fd = 0;
    struct sockaddr_un addr;

    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(fd == -1){
        perror("socket");
        return -1;
    } 
    memset(&addr, 0x0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, MY_SOCKET_PATH, sizeof(addr.sun_path) - 1);

    if(bind(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1)
    {
        perror("bind");
        return -1;
    }
    close(fd);
    return 0;
}


