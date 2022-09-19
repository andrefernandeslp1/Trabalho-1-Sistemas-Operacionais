#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
  int n1, m1, n2, m2, tempo;

  if(argc == 5)
  {
    n1 = atoi(argv[1]);
    m1 = atoi(argv[2]);
    n2 = atoi(argv[3]);
    m2 = atoi(argv[4]);
  }
  else
    printf("Parametros invalidos\n");

  srand(time(NULL));
  double random, random2;

  double matriz1[n1][m1], matriz2[n2][m2];

  FILE *arq, *arq2;
  arq = fopen("matriz_1.txt", "w");
  arq2 = fopen("matriz_2.txt", "w");

  //matriz 1
  tempo = time(NULL);
  fprintf(arq, "%d %d\n", n1, m1);

  for(int i=0 ; i < n1 ; i++)
  {
    for(int j=0 ; j < m1 ; j++)
    {
      random2 = (double)rand();
      random = (double)rand() / random2;
      matriz1[i][j] = random;
      fprintf(arq, "a%d%d %.3f\n", i+1, j+1, random);
      usleep(100000);
    }
  }
  
  tempo = time(NULL) - tempo;
  fprintf(arq, "%d", tempo);

  fclose(arq);

  //matriz 2
  tempo = time(NULL);
  fprintf(arq2, "%d %d\n", n2, m2);

  for(int i=0 ; i < n2 ; i++)
  {
    for(int j=0 ; j < m2 ; j++)
    {
      random2 = (double)rand();
      random = (double)rand() / random2;
      matriz1[i][j] = random;
      fprintf(arq2, "b%d%d %.3f\n", i+1, j+1, random);
      usleep(100000);
    }
  }
  tempo = time(NULL) - tempo;
  fprintf(arq2, "%d", tempo);
  
  fclose(arq2);

  return 0;
}