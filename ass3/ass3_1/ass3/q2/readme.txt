Interprocess Communication
----------------------------

String format:

Total 16 characters : 2 characters for index
                      14 characters for message


Unix Domain Sockets:

Server : calls used for setting up socket:
	socket()
	bind()
	listen()
	accept()
      message tranfer:
        write()
	read()

Client : calls used for setting connection:
        socket()
	connect()
      message tranfer:
        write()
	read()

The operations are blocking and messages are sent and received in order


Fifo:

Server : calls used for setting up:
	mkfifo()
	open()
      message transfer:
	write
	read

Client: calls used for setting up:
	open()
      message transfer:
	write
	read

The operations are blocking and messages are sent and received in order

Shared Memory:

Server/Client : calls used for setting up:
	mq_open()
     message transfer:
	mq_send
	mq_receive

The operations are not blocking and messages are not received in order
