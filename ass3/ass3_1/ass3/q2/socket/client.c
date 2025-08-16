//#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
//#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	char* rand_str[50];

	int i, j;

	int fd;
	if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
		printf("socket creation at client not successfull\n");
		return 1;
    	}

	struct sockaddr_un ser_soc;
	ser_soc.sun_family = AF_UNIX;
        strcpy(ser_soc.sun_path, "server_socket");

	int ret = connect(fd, (struct sockaddr *)&ser_soc, sizeof(struct sockaddr_un));
   	if (ret < 0)
    	{
		printf("socket connection at client not successfull\n");
		return 1;
    	}

	int index = 0;

	while (index < 10) {
		char buffer[4] = {0};
		char cbuffer[126] = {0};

                if (read(fd, cbuffer, sizeof(cbuffer)) < 0) {
			printf("message reading at client not successfull\n");
			return 1;
   		}

                printf("message received at client: %s\n", cbuffer);

		int cindex = cbuffer[1] + 4;
		buffer[0] = cbuffer[0];
		buffer[1] = cindex ;
		buffer[2] = '\0';
		if (write(fd, buffer, sizeof(buffer)) < 0) {
			printf("message writing at client not successfull\n");
			return 1;
		}

          
		index = index +1;
	}

    	close(fd);

}
