#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_t phil[5];
int forks[5];

void phil_action(int *no)
{
  int n = *no;

  if (forks[n] == 0 && forks[(n+1)%5] == 0) {
  	forks[n] = 1;
  	forks[(n+1)%5] = 1;
  	printf("\nPhilosopher %d got the forks", n);
  	sleep(1);
  	forks[n] = 0;
  	forks[(n+1)%5] = 0;
  	printf("\nPhilosopher %d released the forks", n);
  }

}
 
int main()
{
  int i, status_message;
  void *msg;
  int num[5];
  int iter = 10;

  for (i = 0; i < 4; i++) {
     forks[i] = 0;
  }

  while (1) {
    i =0;
    num[i] = i;
    status_message = pthread_create(&phil[i], NULL, (void *)phil_action, (int *)&(num[i]));
    if (status_message != 0)
    {
      printf("\n Thread creation error \n");
      exit(1);
    }
    i = 2;
    num[i] = i;
    status_message = pthread_create(&phil[i], NULL, (void *)phil_action, (int *)&(num[i]));
    if (status_message != 0)
    {
      printf("\n Thread creation error \n");
      exit(1);
    }

    i =0;
    status_message = pthread_join(phil[i], &msg);
    if (status_message != 0)
    {
      printf("\n Thread join failed \n");
      exit(1);
    }
    i =2;
    status_message = pthread_join(phil[i], &msg);
    if (status_message != 0)
    {
      printf("\n Thread join failed \n");
      exit(1);
    }


    i =1;
    num[i] = i;
    status_message = pthread_create(&phil[i], NULL, (void *)phil_action, (int *)&(num[i]));
    if (status_message != 0)
    {
      printf("\n Thread creation error \n");
      exit(1);
    }
    i = 3;
    num[i] = i;
    status_message = pthread_create(&phil[i], NULL, (void *)phil_action, (int *)&(num[i]));
    if (status_message != 0)
    {
      printf("\n Thread creation error \n");
      exit(1);
    }

    i =1;
    status_message = pthread_join(phil[i], &msg);
    if (status_message != 0)
    {
      printf("\n Thread join failed \n");
      exit(1);
    }
    i =3;
    status_message = pthread_join(phil[i], &msg);
    if (status_message != 0)
    {
      printf("\n Thread join failed \n");
      exit(1);
    }

    i = 4;
    num[i] = i;
    status_message = pthread_create(&phil[i], NULL, (void *)phil_action, (int *)&(num[i]));
    if (status_message != 0)
    {
      printf("\n Thread creation error \n");
      exit(1);
    }

    i =4;
    status_message = pthread_join(phil[i], &msg);
    if (status_message != 0)
    {
      printf("\n Thread join failed \n");
      exit(1);
    }
    iter --;
    if (iter <=0)
 	break;

  }
  return 0;
}
