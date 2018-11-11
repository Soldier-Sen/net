all: client server

LOCAL_PATH = $(shell pwd)

LOCAL_CLIENT_SRC := $(LOCAL_PATH)/sock_tcp_client_p203.c
LOCAL_SERVER_SRC := $(LOCAL_PATH)/sock_tcp_server_p203.c

client: sock_tcp_client_p203.o
	gcc -Wall -o client sock_tcp_client_p203.o
server: sock_tcp_server_p203.o
	gcc -Wall -o server sock_tcp_server_p203.o

clean:
	rm -f *.o client server

