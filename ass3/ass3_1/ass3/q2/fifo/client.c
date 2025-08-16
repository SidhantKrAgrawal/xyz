//#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
//#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/fcntl.h>

int main() {
	char* rand_str[50];

	int i, j;

	int index = 0;

	while (index < 10) {
		char buffer[4] = {0};
		char cbuffer[126] = {0};
		int fd;

		fd = open("./fifo", O_RDONLY);

                if (read(fd, cbuffer, sizeof(cbuffer)) < 0) {
			printf("message reading at client not successfull\n");
			return 1;
   		}

                printf("message received at client: %s\n", cbuffer);

		close(fd);
		int cindex = cbuffer[1] + 4;
		buffer[0] = cbuffer[0];
		buffer[1] = cindex ;
		buffer[2] = '\0';
		fd = open("./fifo", O_WRONLY);
		if (write(fd, buffer, sizeof(buffer)) < 0) {
			printf("message writing at client not successfull\n");
			return 1;
		}

          
		close(fd);
		index = index +1;
	}


}
