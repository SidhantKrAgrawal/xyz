#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

pthread_t phil[5];
sem_t forks[5];
sem_t bowl;

void phil_action(int *no)
{
  int n = *no;
  int iter = 10;

 while (1) {
  printf("\nPhilosopher %d waiting for the forks", n);

  if (n%2 == 0) {
  	sem_wait(&forks[n]);
  	sem_wait(&forks[(n + 1) % 5]);
  }
  else {
  	sem_wait(&forks[(n + 1) % 5]);
  	sem_wait(&forks[n]);
  }
  sem_wait(&bowl);
  printf("\nPhilosopher %d got the forks and bowl", n);
  sleep(1);
  sem_post(&bowl);
  sem_post(&forks[n]);
  sem_post(&forks[(n + 1) % 5]);
  printf("\nPhilosopher %d released the forks and bowl", n);
  sleep(5);
  iter --;
  if (iter <= 0)
	break;
 }
}
 
int main()
{
  int i, status_message;
  void *msg;
  int num[5];

  sem_init(&bowl, 0, 2);
  for (i = 0; i <= 4; i++)
  {
    num[i] = i;
    sem_init(&forks[i], 0,1);
  }

  for (i = 0; i <= 4; i++)
  {
    status_message = pthread_create(&phil[i], NULL, (void *)phil_action, (int *)&(num[i]));
    if (status_message != 0)
    {
      printf("\n Thread creation error \n");
      exit(1);
    }
  }

  for (i = 0; i <= 4; i++)
  {
    status_message = pthread_join(phil[i], &msg);
    if (status_message != 0)
    {
      printf("\n Thread join failed \n");
      exit(1);
    }
  }

  for (i = 0; i <= 4; i++)
  {
 	sem_destroy(&forks[i]);
  }
  return 0;
}
