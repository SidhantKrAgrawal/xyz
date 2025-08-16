//#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
//#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/fcntl.h>
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

	mkfifo("./fifo", 06666);
	int index = 0;

	while (index < 50) {
		int fd;
		char buffer[126] = {0};
		char cbuffer[126] = {0};

		fd = open("./fifo", O_WRONLY);

		for ( i = 0; i < 5; i++) {
			strcat(buffer,rand_str[index]);
			index = index +1;
		}

		if (write(fd, buffer, sizeof(buffer)) < 0) {
			printf("message writing at server not successfull\n");
			return 1;
		}

		close(fd);

		fd = open("./fifo", O_RDONLY);
                if (read(fd, cbuffer, sizeof(cbuffer)) < 0) {
			printf("message reading at server not successfull\n");
			return 1;
   		}
          
                printf("Index received at server: %s\n", cbuffer);
    		close(fd);
	}

    	unlink("./fifo");
	clock_gettime(CLOCK_REALTIME, &(finish[i]));
	sub_timespec(start[i], finish[i], &delta);
    	double m = (int)delta.tv_sec + ((float)delta.tv_nsec/1000000000);
	printf("Time taken to transfer through fifo  %lf\n", m);
    	return 0;

}
