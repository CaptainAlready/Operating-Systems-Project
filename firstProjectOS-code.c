#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>

sem_t sem1;
sem_t sem2;
sem_t sem3;
int i=0;

void * fun1(void )
{
    while(1)
    {
    sem_wait(&sem1);
    printf("P");
    printf("I");
    sem_post(&sem2);
    
    }
    

}

void * fun2(void)
{
   while(1)
   {
    sem_wait(&sem2);
    sem_wait(&sem3);
    printf("Z");
    sem_post(&sem3);
       
   }
    
}

void * fun3 (void )
{
    while(1)
   {
    sem_wait(&sem3);
    printf("A");
    sem_post(&sem1);
    
   }
    
    

}

int main()
{
   pthread_t t1;
   pthread_t t2;
   pthread_t t3;


   sem_init(&sem1,0,1);
   sem_init(&sem2,0,1);
   sem_init(&sem3,0,0);

   pthread_create(&t1,NULL,&fun1,NULL);
   pthread_create(&t2,NULL,&fun2,NULL);
   pthread_create(&t3,NULL,&fun3,NULL);

   pthread_join(t1,NULL);
    sleep(1);
   pthread_join(t2,NULL);
    sleep(1);
   pthread_join(t3,NULL);
    sleep(1);

   sem_destroy(&sem1);
   sem_destroy(&sem2);
   sem_destroy(&sem3);

   return 1;
}
