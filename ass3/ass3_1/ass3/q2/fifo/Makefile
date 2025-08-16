all: server client
	./server &
	sleep 1
	./client

server: server.c
	gcc server.c -o server

client: client.c
	gcc client.c -o client
 
