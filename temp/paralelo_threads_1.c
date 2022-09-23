#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

//comando: ./<programa> <matriz_1> <matriz_2> <numero inteiro>

struct Dados
{
  int i, j, linhaA, linhaB, colunaA, colunaB, n, p;
  double **matrizA, **matrizB;
  char *str;
  int *tid;
};

void* hello_world(void * arg)
{
  struct Dados *dados = (struct Dados*) arg;
  printf("Hello World. Esta eh a Thread %d\n", (int)(size_t)dados->tid);
  int tempo = time(NULL);
  //int i = dados->i, j = dados->j;

  int cont=0;
  double aux=0;
  FILE *arq3;
  for( dados->i; dados->i < dados->linhaA; dados->i++) {
    for( dados->j; dados->j < dados->colunaB; dados->j++) {
      if(cont == 0)
      {        
        sprintf(dados->str, "matrizes_threads/matriz_3.%d.txt", dados->n);
        arq3 = fopen(dados->str, "w");
        fprintf(arq3, "%d %d\n", dados->linhaA, dados->colunaB);
        
      }
      for(int k = 0; k < dados->linhaB; k++) {
        aux += dados->matrizA[dados->i][k] * dados->matrizB[k][dados->j];
      }
      if(cont < dados->p - 1)
      {
        fprintf(arq3, "c(%d,%d) %.3lf\n", dados->i+1, dados->j+1, aux);
        cont++;
      }
      else
      {
        fprintf(arq3, "c(%d,%d) %.3lf\n", dados->i+1, dados->j+1, aux);
        tempo = time(NULL) - tempo;
        fprintf(arq3, "%d", tempo);
        fclose(arq3);
        pthread_exit(NULL);
        //cont = 0;
        //dados.n++;
      }
      aux = 0;
      printf("i = %d , j = %d\n", dados->i, dados->j);
    }
	}

  pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
  struct Dados *dados;
  int linhaA, linhaB, colunaA, colunaB, linhaC, colunaC, cont, N, n=0, tempo, p;
  //double aux;
  char *temp;
  temp = malloc(sizeof(char));

  FILE *arq, *arq2, *arq3;
  arq = fopen(argv[1], "r");
  arq2 = fopen(argv[2], "r");
  p = atoi(argv[3]);
  fscanf(arq, "%d %d", &linhaA, &colunaA);
  fscanf(arq2, "%d %d", &linhaB, &colunaB);

  N = (linhaA*colunaB)/p;  

  //double **matrizA, **matrizB;

  // aloca um vetor de LIN ponteiros para linhas
  dados->matrizA = malloc (linhaA * sizeof (double*)) ;
  dados->matrizB = malloc (linhaB * sizeof (double*)) ;

  dados->str = malloc (sizeof(char));

  // aloca cada uma das linhas
  for (int i=0; i < linhaA; i++){
    dados->matrizA[i] = malloc (colunaA * sizeof (double)) ;
  }
  for (int i=0; i < linhaB; i++){
    dados->matrizB[i] = malloc (colunaB * sizeof (double)) ;
  }

  dados->matrizA[0][0] = 1;
  printf("dados.matrizA[0] = %lf", dados->matrizA[0][0]);

  printf("Teste\n");

  // percorre as matrizes
  for (int i=0; i < linhaA; i++)
    for (int j=0; j < colunaA; j++)
      fscanf(arq, "%s %lf", temp, &dados->matrizA[i][j]);
  for (int i=0; i < linhaB; i++)
    for (int j=0; j < colunaB; j++)
      fscanf(arq2, "%s %lf", temp, &dados->matrizB[i][j]);

  printf("Teste\n");

  printf("Teste\n");

  //struct recebe dados
  dados->linhaA = linhaA;
  dados->linhaB = linhaB;
  dados->colunaA = colunaA;
  dados->colunaB = colunaB;
  dados->p = p;
  dados->n = 0;
  dados->i=0;
  dados->j=0;  

  //thread //multiplicação das matrizes
  pthread_t *thread;
  thread = malloc (N * sizeof(pthread_t));

  int status;
  void * thread_return;
  
  for( int i=0 ; i < N; i++) {

    printf("Processo principal criando thread\n");
    status = pthread_create(&thread[dados->n], NULL, (void*)hello_world, &dados);
    if(status != 0)
    {
      printf("Erro na criacao da thread. Codigo de Erro:%d\n", status);
      return 1;
    }
    
    printf ( "Esperando Thread %d finalizar .... \n" , i ) ;
    pthread_join ( thread [ i ] , & thread_return ) ;
    printf ( "Thread %d finalizada \n" , i ) ;
    
    printf("i = %d , j = %d\n", dados->i, dados->j);
    dados->n++;
    
	}

  printf ( "processo vai finalizar \n" ) ;
  
  fclose(arq);
  fclose(arq2);
  //fclose(arq3);

  // libera a memória das matrizes
  for (int i=0; i < linhaA; i++)
    free (dados->matrizA[i]) ;
  free (dados->matrizA) ;

  for (int i=0; i < linhaB; i++)
    free (dados->matrizB[i]) ;
  free (dados->matrizB) ;

  free(temp);
  
 return 0;
}