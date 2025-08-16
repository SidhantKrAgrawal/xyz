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
	int fdr, fdw;

	while (index < 10) {
		char buffer[4] = {0};
		char cbuffer[126] = {0};

		fdr = mq_open("/wmqueue", O_RDONLY);

                if (mq_receive(fdr, cbuffer, sizeof(cbuffer),0) < 0) {
			printf("message reading at client not successfull\n");
			return 1;
   		}

                printf("message received at client: %s\n", cbuffer);

		mq_close(fdr);
		int cindex = cbuffer[1] + 4;
		buffer[0] = cbuffer[0];
		buffer[1] = cindex ;
		buffer[2] = '\0';

		fdw = mq_open("/rmqueue", O_WRONLY);
		if (mq_send(fdw, buffer, sizeof(buffer),0) < 0) {
			printf("message writing at client not successfull\n");
			return 1;
		}

          
		mq_close(fdw);
		index = index +1;
	}


}
