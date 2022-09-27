#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// ./leitura_dados <qtd_de_arquivos>

int main(int argc, char *argv[])
{
  FILE *arq, *arq2, *arq3, *arq4;

  int N, t1, t2, t3, aux=0, aux2=0;
  char tempo_p[10];
  char tempo_t[10];
  char tempo_s[10];
  char str[50], str2[50];
  //str = malloc(sizeof(char));
  //str2 = malloc(sizeof(char));
  //tempo = malloc(sizeof(char));

  N = atoi(argv[1]);

  for(int ii = 1; ii <=N ; ii++)
  {
    sprintf(str,"matrizes_processos/matriz_C%d.txt", ii);
    arq = fopen(str,"r");

    while(!feof(arq)){
      fgets(tempo_p,5,arq);
    }
    t1 = atoi(tempo_p);
    if(t1 > aux) aux = t1;

    fclose(arq);

    sprintf(str2,"matrizes_threads/matriz_C%d.txt", ii);
    arq2 = fopen(str2,"r");
    
    while(!feof(arq2)){
      fgets(tempo_t,5,arq);
    }
    t2 = atoi(tempo_t);
    if(t2 > aux2) aux2 = t2;

    fclose(arq2);
    /*
    if( ii == 1 )
    {
      arq3 = fopen("resultados.txt", "w");
      fprintf(arq3,"Execucao,Paralelo_Threads,Paralelo_Processos\n");
    }
    */
  }

  arq3 = fopen("matriz_3.txt", "r");
  while(!feof(arq3)){
      fgets(tempo_s,5,arq);
    }
  t3 = atoi(tempo_s);
  fclose(arq3);

  int execucao = atoi(argv[2]);

  arq4 = fopen("resultados.txt", "a");
  fprintf(arq4, "%d,%d,%d,%d\n", execucao, aux, aux2, t3);
  fclose(arq4);
  //tempo = NULL;
  
  //free(tempo);
  //free(str);
  //free(str2);

  return 0;
}