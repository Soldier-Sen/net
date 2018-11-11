#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/socket.h>

int isSocketType(int fd)
{
    struct stat st;
    int err = fstat(fd, &st);
    if(err < 0){
        perror("fstat");
        return -1;
    }
    if((st.st_mode & S_IFMT) == S_IFSOCK){
        return 1;
    }
    else{
        return 0;
    }
}

int main(int argc, char *argv[])
{
    int fd = 0;
    int ret = isSocketType(fd);
    printf("fd=%d, type: %s\n", fd, ret == 1 ? "socket":"no socket");
    
    int s = socket(AF_INET, SOCK_STREAM, 0);
    ret = isSocketType(s);
    fd = s;
    printf("fd=%d, type: %s\n", fd, ret == 1 ? "socket":"no socket");
    close(s);

    return 0;
}
