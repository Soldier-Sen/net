#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char *argv[])
{
    struct in_addr ip, local, network;
    char addr1[] = "192.168.1.1";
    char addr2[] = "255.255.255.255";
    char addr3[] = "192.168.1";
    char *str1 = NULL, *str2 = NULL;
    int err = 0;

    /*测试函数inet_aton,将点分四段式IP地址转为地址结构in_addr值*/
    err = inet_aton(addr1, &ip);
    if(err){
        printf("inet_aton: %s -> 0x%x\n", addr1, ip.s_addr);
    }
    else{
        printf("inet_aton: %s -> error!\n", addr1);
    }
    str1 = inet_ntoa(ip);
    printf("inet_ntoa: ip=0x%x, str1:%s\n\n", ip.s_addr, str1);
    
    /*测试inet_addr函数*/
    err = ip.s_addr = inet_addr(addr1);
    if(err != -1){
        printf("inet_addr: %s -> 0x%x\n", addr1, ip.s_addr);
    }
    else{
        printf("inet_addr: %s -> error!\n", addr1);
    }
    err = ip.s_addr = inet_addr(addr2);
    if(err != -1){
        printf("inet_addr: %s -> 0x%x\n\n", addr2, ip.s_addr);
    }
    else{
        printf("inet_addr: %s -> error!\n\n", addr2);
    }
    
    /*测试函数inet_ntoa, 不可重入*/
    ip.s_addr = 192<<24 | 168<<16 | 2<<8 | 1;
    ip.s_addr = htonl(ip.s_addr);
    str1 = inet_ntoa(ip);//按网络字节序处理
    printf("inet_ntoa: ip=0x%x, str1:%s\n", ip.s_addr, str1);
    ip.s_addr = 255<<24 | 255<<16 | 255<<8 | 255;
    str2 = inet_ntoa(ip);
    printf("inet_ntoa: ip=0x%x, str1:%s, str2:%s\n\n", ip.s_addr, str1, str2);
    
    /*测试函数inet_addr*/
    err = ip.s_addr = inet_addr(addr3);
    if(err != -1){
        printf("inet_addr: %s -> 0x%x\n", addr3, ip.s_addr);
    }
    else{
        printf("inet_addr: %s -> error!\n", addr3);
    }
    str1 = inet_ntoa(ip);
    printf("inet_ntoa: %s -> 0x%x\n\n", str1, ip.s_addr);

    /*测试函数inet_lnaof, 获得本机地址.只取四段式IP的最后一段*/ 
    inet_aton(addr1, &ip);
    local.s_addr = htonl(ip.s_addr);
    printf("addr1: %s -> 0x%x\n", addr1, local.s_addr);
    local.s_addr = inet_lnaof(ip);
    str1 = inet_ntoa(local);
    printf("inet_lnaof: %s -> 0x%x\n\n", str1, local.s_addr);

    /*测试函数inet_netof,获得本机地址,只取四段式IP地址的前三段*/
    network.s_addr = (inet_netof(ip));
    printf("inet_netof: %s -> 0x%x\n", inet_ntoa(network), network.s_addr);
    //-------------
    char IPSTR[] = "192.168.3.1";
    #define ADDRLEN    16
    char addr[16] = {0};
    const char *str = NULL;
    /*测试函数inet_pton,转换IPST为二进制形式*/
    err = inet_pton(AF_INET, IPSTR, &ip);
    if(err > 0){
        printf("inet_pton: %s -> 0x%x\n", IPSTR, ip.s_addr);
    }
    /*测试函数inet_ntop, 转换二进制的192.168.4.1为字符串*/
    ip.s_addr = htonl(192<<24 | 168<<16 | 4<<8 | 1);
    str = inet_ntop(AF_INET, &ip, addr, sizeof(addr));
    if(str){
        printf("inet_pton: %s -> 0x%x\n", str, ip.s_addr);
    }

    return 0;
}


/*
1.将点分四段式IP地址转为地址结构in_addr值
int inet_aton(const char *cp, struct in_addr *inp);

2.将字符串转为in_addr值
in_addr_t inet_addr(const char *cp)

3.将字符串的地址的网络部分转为in_addr类型
in_addr_t inet_network(const char *cp)

4.将in_addr地址结构转为字符串
char *inet_ntoa(struct in_addr in)

5.将网络地址和主机地址合成为IP地址
struct in_addr inet_makeaddr(int net, int host)

6.获得IP地址的主机部分
in_addr_t inet_lnaof(struct in_addr in)

7.获得IP地址的网络部分
in_addr_t inet_netof(struct in_addr in)

struct in_addr{
    unsigned long int s_addr; //IP地址
}

8.将字符串类型的IP地址转换为二进制类型,安全可重入.返回正直才是成功
int inet_pton(int af, const char *src, void *dst)
9.将二进制的网络IP地址转换为字符串 const char *inet_ntop(int af, const void *src, char *dst, socklen_t cnt)
*/


