#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// ./cria_arquivo_resultados_E2

int main()
{
  FILE *arq, *arq2, *arq3, *arq4;

  int N, t1, t2, t3, aux=0, aux2=0, tam1, tam2, p;

  arq = fopen("matriz_1.txt", "r");

  fscanf(arq,"%d %d", &tam1, &aux);
  
  fclose(arq);

  arq2 = fopen("matriz_2.txt", "r");

  fscanf(arq2,"%d %d", &aux2, &tam2);
  
  fclose(arq2);

  arq4 = fopen("resultados_E2.txt", "w");
  fprintf(arq4, "Matriz: %d x %d\n", tam1, tam2);
  fprintf(arq4, "P,Paralelo_Processos,Paralelo_Threads\n");
  fclose(arq4);

  return 0;
}