#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include<semaphore.h>
#include<fcntl.h>
#include <curses.h>
#define N 4

int *pinakas;
sem_t smoker[3];
sem_t SellerSem;
int *randomnum;



void xartis(){
    while(true){
// printf("o xartis\n");  //exei xarti
sem_wait(&smoker[1]);
*(pinakas + 0)=0;
*(pinakas + 1)=0;
printf("phre o xartis kapno kai spirta\n\n");
sem_post(&SellerSem);
}
}


void kapnos(){
    while(true){
// printf("O kapnos\n");   //exei kapno

   sem_wait(&smoker[0]);
   *(pinakas + 0)=0;
   *(pinakas + 2)=0;
   printf("O kapnos phre xarti kai spirta\n\n");
   sem_post(&SellerSem);

   }
}

void spirtos(){
    while(true){
// printf("o spirtos");  //exei spirta
    sem_wait(&smoker[2]);
    *(pinakas + 1)=0;
    *(pinakas + 2)=0;
printf("phre o spirtos xarti kai kapno\n\n");
    sem_post(&SellerSem);
    }
}

void consumer(){
    while(true){
        int temp=*randomnum;
        temp=rand()%3;
        *randomnum=temp;
        sem_wait(&SellerSem);
        printf("O Seler dialegei epilogh : %d\n\n",temp);
        if(temp==0){ //topothetoume xarti kai spirta ara theloume kapno
            *(pinakas + 0)=1;
            *(pinakas + 2)=1;
            sem_post(&smoker[0]);
  
        }
        else if(temp==1){ //topothetoume kapno kai spirta kai theloume xarti
            *(pinakas + 0)=1;
            *(pinakas + 1)=1;
            sem_post(&smoker[1]);
     
        }
        else{                  //topothetoume kapno kai xarti kai theloume spirta
            *(pinakas + 1)=1;
            *(pinakas + 2)=1;
            sem_post(&smoker[2]);
         
        }
    
        }
}
    
    

    


int main ()
{
    
    int shmid3= shmget(IPC_PRIVATE, 3*sizeof (int),0666 | IPC_CREAT);
    if (shmid3< 0) {
    perror ("shmget\n");
    exit (1);
        }
    pinakas = (int * )shmat (shmid3, NULL, 0);

    
    int shmid2= shmget(IPC_PRIVATE, sizeof (int),0666 | IPC_CREAT);
    if (shmid2< 0) {
    perror ("shmget\n");
    exit (1);
        }
    randomnum = (int * )shmat (shmid3, NULL, 0);

    
    
    
    
sem_init(&smoker[0], 1,0);
sem_init(&smoker[1], 1,0);
sem_init(&smoker[2], 1,0);
sem_init(&SellerSem, 1,1);
 
    for(int i=0; i<1; i ++) if(fork()==0) {consumer(); break;}
    for(int i=0; i<1; i ++) if(fork()==0) {xartis(); break;}
    for(int i=0; i<1; i ++) if(fork()==0) {kapnos(); break;}
    for(int i=0; i<1; i ++) if(fork()==0) {spirtos(); break;}

}


