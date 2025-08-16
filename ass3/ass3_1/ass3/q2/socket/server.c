//#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
//#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef long long int ll;

void sub_timespec(struct timespec t1, struct timespec t2, struct timespec *td)
{
    ll NS_PER_SECOND = 1000000000;

    td->tv_nsec = t2.tv_nsec - t1.tv_nsec;
    td->tv_sec  = t2.tv_sec - t1.tv_sec;
    if (td->tv_sec > 0 && td->tv_nsec < 0)
    {
        td->tv_nsec += NS_PER_SECOND;
        td->tv_sec--;
    }
    else if (td->tv_sec < 0 && td->tv_nsec > 0)
    {
        td->tv_nsec -= NS_PER_SECOND;
        td->tv_sec++;
    }
}

int main() {
	char* rand_str[50];

	int i, j;

	struct timespec start[3], finish[3], delta;
    	clock_gettime(CLOCK_REALTIME, &(start[i]));

	for (i = 0; i < 50; i++) {
		rand_str[i] = (char *)malloc(sizeof(char) * 20);
		rand_str[i][0] = i/10 + '0';
		rand_str[i][1] = i%10 + '0';
		for (j = 2; j < 16; j++) {
			rand_str[i][j] = i + 'A';
		}
		rand_str[i][16] = '\0';
	}

	int fd;
	if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
		printf("socket creation at server not successfull\n");
		return 1;
    	}

	struct sockaddr_un ser_soc;
	ser_soc.sun_family = AF_UNIX;
        strcpy(ser_soc.sun_path, "server_socket");

        //sleep(3);
	int ret = bind(fd, (struct sockaddr *)&ser_soc, sizeof(struct sockaddr_un));
   	if (ret < 0)
    	{
    		unlink("server_socket");
		
		printf("socket binding at server not successfull\n");
		return 1;
    	}

	listen(fd, 2); 
    	int msgid = accept(fd, 0, 0);

	int index = 0;

	while (index < 50) {
		char buffer[126] = {0};
		char cbuffer[126] = {0};

		for ( i = 0; i < 5; i++) {
			strcat(buffer,rand_str[index]);
			index = index +1;
		}

		if (write(msgid, buffer, sizeof(buffer)) < 0) {
			printf("message writing at server not successfull\n");
			return 1;
		}

                if (read(msgid, cbuffer, sizeof(cbuffer)) < 0) {
			printf("message reading at server not successfull\n");
			return 1;
   		}
          
                printf("Index received at server: %s\n", cbuffer);
	}

    	unlink("server_socket");
	close(msgid);
    	close(fd);
//    	unlink("server_socket");
    	shutdown(fd, SHUT_RDWR);

	clock_gettime(CLOCK_REALTIME, &(finish[i]));
	sub_timespec(start[i], finish[i], &delta);
    	double m = (int)delta.tv_sec + ((float)delta.tv_nsec/1000000000);
	printf("Time taken to transfer through socket  %lf\n", m);
    	return 0;

}
