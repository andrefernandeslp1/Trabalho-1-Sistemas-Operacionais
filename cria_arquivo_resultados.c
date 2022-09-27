#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// ./cria_arquivo_resultados <valor de P>

int main(int argc, char *argv[])
{
  FILE *arq, *arq2, *arq3, *arq4;

  int N, t1, t2, t3, aux=0, aux2=0, tam1, tam2, p;
  //char tempo_p[10];
  //char tempo_t[10];
  //char tempo_s[10];
  //char str[50], str2[50];
  //str = malloc(sizeof(char));
  //str2 = malloc(sizeof(char));
  //tempo = malloc(sizeof(char));

  p = atoi(argv[1]);

  arq3 = fopen("matriz_3.txt", "r");

  fscanf(arq3,"%d %d", &tam1, &tam2);
  
  fclose(arq3);

  char str3[50];
  sprintf(str3, "resultados_%dx%d_p%d.txt", tam1, tam2, p);
  arq4 = fopen(str3, "w");
  fprintf(arq4, "Execucao,Paralelo_Threads,Paralelo_Processos,Sequencial\n");
  fclose(arq4);
  //tempo = NULL;
  
  //free(tempo);
  //free(str);
  //free(str2);

  return 0;
}