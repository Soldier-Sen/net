#include <stdio.h>
#include <arpa/inet.h>

/*
联合类型的变量类型，用于测试字节序
成员value的高低端字节可以有成员type按字节访问
*/
typedef union{
    unsigned short int value;
    unsigned char byte[2];
}to16;

typedef union{
    unsigned int value;
    unsigned char byte[4];
}to32;

#define BITS16 16
#define BITS32 32

void showvalue(unsigned char *begin, int flag)
{
    int num = 0;
    int i = 0;
    if(flag == BITS16){
        num = 2;
    }
    else if(flag == BITS32){
        num = 4;
    }
    for(i = 0; i < num; i++){
        printf("%x ", *(begin+i));
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    to16 v16_orig, v16_turn1, v16_turn2;
    to32 v32_orig, v32_turn1, v32_turn2;
    printf("sizeof(long):%ld\n\n", sizeof(long));

    v16_orig.value = 0xabcd;
    v16_turn1.value = htons(v16_orig.value);
    v16_turn2.value = htons(v16_turn1.value);

    v32_orig.value = 0x12345678;
    v32_turn1.value = htonl(v32_orig.value);
    v32_turn2.value = htonl(v32_turn1.value);

    /*打印结果*/
    printf("16 主机字节序转网络字节序:\n\t");
    printf("orig:\t");
    /*１６原始值*/
    showvalue(v16_orig.byte, BITS16);
    /*１６第一次转换值*/
    printf("\t1 time:\t");
    showvalue(v16_turn1.byte, BITS16);
    /*１６第二次转换值*/
    printf("\t2 time:\t");
    showvalue(v16_turn2.byte, BITS16);

    printf("32 主机字节序转网络字节序:\n\t");
    printf("orig:\t");
    /*３２原始值*/
    showvalue(v32_orig.byte, BITS32);
    /*３２第一次转换值*/
    printf("\t1 time:\t");
    showvalue(v32_turn1.byte, BITS32);
    /*３２第二次转换值*/
    printf("\t2 time:\t");
    showvalue(v32_turn2.byte, BITS32);
    return 0;
}
