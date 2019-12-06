
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define N 4

struct thread_data{
      int num_ligne;
      int value;
      char *name;
};

int matrice[N][N];
int found= 0;

void *search(void *data){
      struct thread_data *my_data= (struct thread_data*)data;
      printf("Thread #%d is looking on linge #%d for #%d\n",my_data->num_ligne,my_data->num_ligne,my_data->value);
      for(int j=0; j<N;j++){
            if(matrice[my_data->num_ligne][j] == my_data->value){
                  found = 1;
                  printf("Thread #%d found #%d on --> [%d][%d] \n",my_data->num_ligne,my_data->value,my_data->num_ligne,j);
                  pthread_exit(0);
            }
      }
      pthread_exit(NULL);
}
void initMatrice(void)
{
      for (int i = 0; i < N; i++)
      {
            for (int j = 0; j < N; j++)
            {
                  if (i % 2 == 0){
                        matrice[i][j] = 1*i/(j+1) + 2;
                  }else
                  {
                        matrice[i][j] = N * i + j;
                  }
            }
      }
}
void printMatrice(void)
{
      for (int i = 0; i < N; i++)
      {
            for (int j = 0; j < N; j++)
            {
                  printf("%d\t",matrice[i][j]); 
            }
            printf("\n");
      }
}

int main(int argc, char *argv[])
{
      pthread_t workerThreads[N-1];
      struct thread_data thread_data_array[N-1];
      int value;


      initMatrice();
      printMatrice();
      printf("Donner une valeur: \n");
      scanf("%d",&value);

      for(int id=0;id<N-1;id++){
            thread_data_array[id].name = "Mat";
            thread_data_array[id].num_ligne = id;
            thread_data_array[id].value = value;
            pthread_create(&workerThreads[id],NULL,search,(void *)&thread_data_array[id]);
            pthread_join(workerThreads[id],NULL);
      }

    if(found == 0){
            //look on the last line for a match
            for(int k=0; k<N;k++){
                  if(matrice[N-1][k] == value){
                        printf("value found on --> [%d][%d] by Main:#%ld\n",N,k,pthread_self());
                        pthread_exit(0);
                  }
            }
            printf("404 value not found \n");
      }
      pthread_exit(NULL);
      return 0;
}
