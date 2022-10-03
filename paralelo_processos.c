#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>

//comando: ./<programa> <matriz_1> <matriz_2> <valor_de_P>

int linhaA, linhaB, colunaA, colunaB, linhaC, colunaC, cont, e, elementos, n, tempo, p;
int N;
double **matrizA, **matrizB;

int funcao(int n)
{
  
  int tempo = time(NULL);
  int cont=0;
  double aux;
  FILE *arq3;
  char str_[50];

  int i, j;
	int inicio, final;

  double passo = (double)linhaA/N;

  //if(linhaA % N != 0)
    //passo++;
  //printf("Passo = %lf\n", passo);

  if( n % 2 != 0 )
    j = p % colunaB;
  else  
    j = 0;

  inicio = n * passo;

  final = ceil((n + 1) * passo) - 1;

  if(final > linhaA)
    final = linhaA - 1;

  for( i = inicio; i <= final; i++) {
    for( j ; j < colunaB; j++) {

      if(cont == 0) {       
        sprintf(str_, "matrizes_processos/matriz_C%d.txt", n+1);
        arq3 = fopen(str_, "w");
        fprintf(arq3, "%d %d\n", linhaA, colunaB);
      }

      aux = 0;

      for(int k = 0; k < linhaB; k++) 
        aux += matrizA[i][k] * matrizB[k][j];

      if(cont < p ) {
        fprintf(arq3, "c(%d,%d) %.3lf\n", i+1, j+1, aux);
        cont++;
      }

      //if(cont == colunaB)
      //  j = 0;

      if(cont == p ) {
        tempo = time(NULL) - tempo;
        fprintf(arq3, "%d", tempo);
        fclose(arq3);         
        //return 0;
        exit(0);
      }
    }
    j = 0;
  }
  tempo = time(NULL) - tempo;
  fprintf(arq3, "%d", tempo);
  fclose(arq3);
  //return 0;
  exit(0);
}

int main (int argc, char *argv[])
{
  char temp[100];

  FILE *arq, *arq2;
  arq = fopen(argv[1], "r");
  arq2 = fopen(argv[2], "r");
  p = atoi(argv[3]);
  fscanf(arq, "%d %d", &linhaA, &colunaA);
  fscanf(arq2, "%d %d", &linhaB, &colunaB);

  n = 0; 

  // aloca um vetor de LIN ponteiros para linhas
  matrizA = malloc (linhaA * sizeof (double*)) ;
  matrizB = malloc (linhaB * sizeof (double*)) ;

  // aloca cada uma das linhas
  for (int i=0; i < linhaA; i++){
    matrizA[i] = malloc (colunaA * sizeof (double)) ;
  }
  for (int i=0; i < linhaB; i++){
    matrizB[i] = malloc (colunaB * sizeof (double)) ;
  }

  // percorre as matrizes
  for (int i=0; i < linhaA; i++)
    for (int j=0; j < colunaA; j++)
      fscanf(arq, "%s %lf", temp, &matrizA[i][j]);
  for (int i=0; i < linhaB; i++)
    for (int j=0; j < colunaB; j++)
      fscanf(arq2, "%s %lf", temp, &matrizB[i][j]);

  //thread //multiplicação das matrizes
  N = (linhaA*colunaB) / p;
  if ((linhaA*colunaB) % p != 0)  
    N++;

  pid_t filho;

  for( int i=0 ; i < N; i++) {

    filho = fork();

    if(filho == 0)
    {
      printf("Filho = %d\n", getpid());
      funcao(i);
      //exit(0);
    }
    //wait(NULL);

    //if(filho > 0){
    //  printf("Pai = %d\n", getpid());
    //}
    //wait(NULL);
	}
  wait(NULL);
  /*
  for(int i=0 ; i < N ; i++)
  {
    //printf ( "Esperando Thread %d finalizar .... \n" , i ) ;
    pthread_join ( thread [i] , &thread_return ) ;
    //printf ( "Thread %d finalizada \n" , i ) ;
  }
  */

  //printf ( "processo vai finalizar \n" ) ;

  fclose(arq);
  fclose(arq2);

  // libera a memória das matrizes
  for (int i=0; i < linhaA; i++){
    matrizA[i] = NULL;
    free (matrizA[i]) ;
  }
  matrizA = NULL;
  free (matrizA) ;

  for (int i=0; i < linhaB; i++){
    matrizB[i] = NULL;
    free (matrizB[i]) ;
  }
  matrizB = NULL;
  free (matrizB) ;

  return 0;
}