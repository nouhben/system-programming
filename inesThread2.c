
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define NUM_THREADS 3




void *tache(void *number){
      int value= (int)number;
      printf("thread_ID #%ld --->starts afficher les nombres premiers\n",pthread_self());
      for(int i=1; i<value; i++){
            int numberOfDiv= 2;
            int maxDiv= (int)(sqrt(i));
            for(int j=2; j<=maxDiv;j++){
                  if(i%j == 0)
                        numberOfDiv++;
            }
            if(numberOfDiv == 2){
                  printf("%d\t",i);
            }
      }
     printf("\n[th_id #%ld --->ENDS.\n",pthread_self());
     pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
      pthread_t workerThread;
      printf("Donner une valeur: \n");
      int value;
      scanf("%d",&value);

      pthread_create(&workerThread,NULL,tache,(void *)value);
      pthread_join(workerThread,NULL);
      pthread_exit(NULL);

      return 0;
}
