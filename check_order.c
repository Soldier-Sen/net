#include <stdio.h>

/*
联合类型的变量类型，用于测试字节序
成员value的高低端字节可以有成员type按字节访问
*/
typedef union{
    unsigned short int value;
    unsigned char byte[2];
}to;

int main(int argc, char *argv[])
{
    to order;
    order.value = 0xabcd;
    /*小端字节序检查*/
    if(order.byte[0] == 0xcd && order.byte[1] == 0xab)
    {
        printf("Low endian byte order: byte[0]=0x%x,byte[1]=0x%x\n",
                order.byte[0],
                order.byte[1]);
    }
    /*大端字节序检查*/
    if(order.byte[0] == 0xab && order.byte[1] == 0xcd)
    {
        printf("Big endian byte order: byte[0]=0x%x,byte[1]=0x%x\n",
                order.byte[0],
                order.byte[1]);
    }
    return 0;
}
