#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

//comando: ./<programa> <matriz_1> <matriz_2> <numero inteiro>

struct Dados{
  int i, j, linhaA, linhaB, colunaA, colunaB, e, elementos, N, n, p;
  double **matrizA, **matrizB;
  char *str;
  int *tid;
} dados;

pthread_t *thread;
int status;
void * thread_return;

void * hello_world(void *tid)
{
  //dados = data;
  if ((int)(size_t)tid > 0){
    pthread_join (thread[(size_t)tid - 1], &thread_return) ; //espera a thread especificada terminar
    printf ("Esta é a Thread %d. A Thread %d terminou.\n", (int)(size_t)tid, (int)(size_t)tid - 1);
  }
  else
    printf ("Esta é a PRIMEIRA Thread.\n"); 

  int tempo = time(NULL);
  int cont=0;
  double aux;
  FILE *arq3;

  if(dados.e < dados.elementos)
  {
    for( dados.i; dados.i < dados.linhaA; ) {
      for( dados.j; dados.j < dados.colunaB; ) {
        aux = 0;
        if(cont == 0 && dados.e < dados.elementos) {        
          sprintf(dados.str, "matrizes_threads/matriz_3.%d.txt", dados.n);
          arq3 = fopen(dados.str, "w");
          fprintf(arq3, "%d %d\n", dados.linhaA, dados.colunaB);
        }
        for(int k = 0; k < dados.linhaB; k++) {
          aux += dados.matrizA[dados.i][k] * dados.matrizB[k][dados.j];
        }

        if(cont < dados.p - 1 && dados.e < dados.elementos) {
          dados.e++;
          fprintf(arq3, "c(%d,%d) %.3lf\n", dados.i+1, dados.j+1, aux);
          cont++;
          printf("i = %d , j = %d\n", dados.i, dados.j);
          if(dados.j < dados.colunaB - 1){
            dados.j++;
            if(dados.j == dados.colunaB - 1)
              dados.i++;
          }
          else dados.j = 0;
        }
        if(cont == dados.p - 1) {
          dados.e++;
          printf("i = %d , j = %d\n", dados.i, dados.j);
          if(dados.j == dados.colunaB - 1)
            fprintf(arq3, "c(%d,%d) %.3lf\n", dados.i, dados.j+1, aux);
          else 
            fprintf(arq3, "c(%d,%d) %.3lf\n", dados.i+1, dados.j+1, aux);
          tempo = time(NULL) - tempo;
          fprintf(arq3, "%d", tempo);
          fclose(arq3);
          if(dados.j < dados.colunaB - 1){
            dados.j++;
            if(dados.j == dados.colunaB - 1)
              dados.i++;
          }
          else dados.j = 0;
          pthread_exit(NULL);
        }
      }        
    }
  }
  fclose(arq3);
  pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
  //data *dados;
  int linhaA, linhaB, colunaA, colunaB, linhaC, colunaC, cont, elementos, N, n=0, tempo, p;
  //double aux;
  char *temp;
  temp = malloc(sizeof(char));

  FILE *arq, *arq2;
  arq = fopen(argv[1], "r");
  arq2 = fopen(argv[2], "r");
  p = atoi(argv[3]);
  fscanf(arq, "%d %d", &linhaA, &colunaA);
  fscanf(arq2, "%d %d", &linhaB, &colunaB);

  dados.e = 0;
  dados.elementos = (linhaA*colunaB);
  N = (linhaA*colunaB)/p;  
  thread = malloc (N * sizeof(pthread_t));

  //double **matrizA, **matrizB;

  // aloca um vetor de LIN ponteiros para linhas
  dados.matrizA = malloc (linhaA * sizeof (double*)) ;
  dados.matrizB = malloc (linhaB * sizeof (double*)) ;

  dados.str = malloc (sizeof(char));

  // aloca cada uma das linhas
  for (int i=0; i < linhaA; i++){
    dados.matrizA[i] = malloc (colunaA * sizeof (double)) ;
  }
  for (int i=0; i < linhaB; i++){
    dados.matrizB[i] = malloc (colunaB * sizeof (double)) ;
  }

  // percorre as matrizes
  for (int i=0; i < linhaA; i++)
    for (int j=0; j < colunaA; j++)
      fscanf(arq, "%s %lf", temp, &dados.matrizA[i][j]);
  for (int i=0; i < linhaB; i++)
    for (int j=0; j < colunaB; j++)
      fscanf(arq2, "%s %lf", temp, &dados.matrizB[i][j]);

  //struct recebe dados
  dados.linhaA = linhaA;
  dados.linhaB = linhaB;
  dados.colunaA = colunaA;
  dados.colunaB = colunaB;
  dados.p = p;
  dados.n = 0;
  dados.i = 0;
  dados.j = 0 ;  

  //thread //multiplicação das matrizes
  
  
  for( int i=0 ; i < N; i++) {

    printf ( " Processo principal criando thread #%d \n " , i ) ;
    status = pthread_create (&thread[i], NULL ,hello_world, (void*)(size_t)i) ;
    if(status != 0)
    {
      printf("Erro na criacao da thread. Codigo de Erro:%d\n", status);
      return 1;
    }
    dados.n++;
    printf ( "Esperando Thread %d finalizar .... \n" , i ) ;
    pthread_join ( thread [ i ] , &thread_return ) ;
    printf ( "Thread %d finalizada \n" , i ) ;
    
    //printf("i = %d , j = %d\n", dados.i, dados.j);
    
	}

  printf ( "processo vai finalizar \n" ) ;
  
  fclose(arq);
  fclose(arq2);
  //fclose(arq3);

  // libera a memória das matrizes
  for (int i=0; i < linhaA; i++)
    free (dados.matrizA[i]) ;
  free (dados.matrizA) ;

  for (int i=0; i < linhaB; i++)
    free (dados.matrizB[i]) ;
  free (dados.matrizB) ;

  free(temp);
  
 return 0;
}