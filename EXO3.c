#define N 10

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int marticeA[N][N], marticeB[N][N], marticeC[N][N];
int toure_th1, toure_th2, toure_th3, toure_th4;

void initMatrice(char *name)
{
      for (int i = 0; i < N; i++)
      {
            for (int j = 0; j < N; j++)
            {
                  if (name == 'A')
                        marticeA[i][j] = 1;
                  else
                  {
                        marticeB[i][j] = N * i + j;
                  }
            }
      }
}

void printMatrce(int **matrice, int length, int height)
{
      for (size_t i = 0; i < height; i++)
      {
            for (size_t j = 0; j < length; i++)
            {
                  printf("%d", *(*(matrice + j) + i));
            }
      }
}

void *addMatriceTopLeft(void *t){
      for (size_t i = 0; i < 5; i++)
      {
            for (size_t j = 0; j < 5; j++)
            {
                  marticeC[i][j] = marticeA[i][j] + marticeB[i][j];
            }
      }
      toure_th1 = 1;
      printf("Thread 4 - ENDS\n");
}

void *addMatriceTopRight(void *t)
{
      for (size_t i = 0; i < 5; i++)
      {
            for (size_t j = 5; j < N; j++)
            {
                  marticeC[i][j] = marticeA[i][j] + marticeB[i][j];
            }
      }

      toure_th2 = 1;
      printf("Thread 4 - ENDS\n");
}

void *addMatriceBottomRight(void *t)
{
      for (size_t i = 5; i < N; i++)
      {
            for (size_t j = 0; j < 5; j++)
            {
                  marticeC[i][j] = marticeA[i][j] + marticeB[i][j];
            }
      }
      toure_th3 = 1;
      printf("Thread 4 - ENDS\n");
}

void *addMatriceBottomLeft(void *t)
{

      for (size_t i = 5; i < N; i++)
      {
            for (size_t j = 5; j < N; j++)
            {
                  marticeC[i][j] = marticeA[i][j] + marticeB[i][j];
            }
      }
      toure_th4 = 1;
      printf("Thread 4 - ENDS\n");
}

void *afficherResult(void *t)
{

      while (toure_th1 == 0 || toure_th2 == 0 || toure_th3 == 0 || toure_th4 == 0)
      {
            //wiat for other therads
      }
      printf("Matrice Resultat: \n");

      for (size_t i = 0; i < N; i++)
      {
            for (size_t j = 0; j < N; j++)
            {
                  printf("%d \t", marticeC[i][j]);
            }
            printf("\n");
      }
}



int main(int argc, char const *argv[])
{
      pthread_t pth[5]; //array of four threads

      initMatrice('A');
      initMatrice('B');
    
    

      pthread_create(&pth[0], 0, addMatriceTopLeft, NULL);              //creation of thread 1
      pthread_create(&pth[1], 0, addMatriceTopRight, NULL);             //creation of thread 2

      pthread_create(&pth[2], 0, addMatriceBottomLeft, NULL);             //creation of thread 3
      pthread_create(&pth[3], 0, addMatriceBottomRight, NULL);            //creation of thread 4

      pthread_create(&pth[4], 0, afficherResult, NULL);                  //creation of thread 5
    
    

      pthread_join(pth[0], NULL);                            //execution of thread 1
      pthread_join(pth[1], NULL);                           //execution of thread 2

      pthread_join(pth[2], NULL);                           //execution of thread 3
      pthread_join(pth[3], NULL);                           //execution of thread 4

      pthread_join(pth[4], NULL);                           //execution of thread 5
    
    
    

      //printMatrce(&marticeC, N, N);

      return 0;
}
