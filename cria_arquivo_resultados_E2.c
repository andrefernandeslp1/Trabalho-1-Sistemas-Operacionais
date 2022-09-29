#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// ./cria_arquivo_resultados <valor de P>

int main()
{
  FILE *arq, *arq2, *arq3, *arq4;

  int N, t1, t2, t3, aux=0, aux2=0, tam1, tam2, p;

  arq3 = fopen("matriz_3.txt", "r");

  fscanf(arq3,"%d %d", &tam1, &tam2);
  
  fclose(arq3);

  arq4 = fopen("resultados_E2.txt", "w");
  fprintf(arq4, "Matriz: %d x %d\n", tam1, tam2);
  fprintf(arq4, "P,Paralelo_Processos,Paralelo_Threads\n");
  fclose(arq4);

  return 0;
}