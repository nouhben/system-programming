
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define NUM_THREADS 3




void *tache(void *letter){

      printf("thread_ID #%ld --->starts\n",pthread_self());
      for(int i=0; i<strlen((char*)(letter)); i++){
            //do nothing
            printf("%c \t",((char*)(letter))[i]);
      }
     printf("\n[th_id #%ld --->ENDS.\n",pthread_self());
     pthread_exit(NULL);
}

void *runThreads(void *threads){

      pthread_t *my_threads= (pthread_t *)threads;
      int rc[NUM_THREADS];

      char *message="LETTER";
      rc[0]= pthread_create(&my_threads[0],NULL,tache,(void *)message);
            if(rc[0]){
                  printf("ERROR %d",rc[0]);
                  exit(-1);
            }

      message="CHAR";
      rc[1]= pthread_create(&my_threads[1],NULL,tache,(void *)message);
            if(rc[1]){
                  printf("ERROR %d",rc[1]);
                  exit(-1);
            }

      message="INES";
      rc[2]= pthread_create(&my_threads[2],NULL,tache,(void *)message);
            if(rc[2]){
                  printf("ERROR %d",rc[2]);
                  exit(-1);
            }
      
      //the calling thread can't stop untill all the threads execute exit
      pthread_join(my_threads[0],NULL);
      pthread_join(my_threads[1],NULL);
      pthread_join(my_threads[2],NULL);
 
      pthread_exit(NULL);
}
int main(int argc, char *argv[])
{
      pthread_t master_thread;

      pthread_t threadArray[NUM_THREADS];

      pthread_create(&master_thread,NULL,runThreads,(void *)threadArray);
      pthread_join(master_thread,NULL);
      pthread_exit(NULL);

      return 0;
}
