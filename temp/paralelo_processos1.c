#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

//comando: ./<programa> <matriz_1> <matriz_2> <valor_de_P>

struct Dados{
  int i, j, linhaA, linhaB, colunaA, colunaB, e, elementos, N, n, p;
  double **matrizA, **matrizB;
  char *str;
} dados;

void funcao(int n)
{
  int tempo = time(NULL);
  int cont=0;
  double aux;
  FILE *arq3;
  char str_[50];
//////////////////////////////////////////////
  int i=0, j=0;

  for( i; i < dados.linhaA; ) {
    for( j; j < dados.colunaB; ) {

      if(dados.e < dados.elementos){

        aux = 0;

        if(cont == 0) {        
          sprintf(str_, "matrizes_threads/matriz_C%d.txt", n+1);
          arq3 = fopen(str_, "w");
          fprintf(arq3, "%d %d\n", dados.linhaA, dados.colunaB);
        }
        
        for(int k = 0; k < dados.linhaB; k++) 
          aux += dados.matrizA[i][k] * dados.matrizB[k][j];

        if(cont < dados.p ) {
          fprintf(arq3, "c(%d,%d) %.3lf\n", i+1, j+1, aux);
          dados.e++;
          cont++;
          if(j < dados.colunaB - 1) {
            j++;
          }
          else {
            j = 0;
            i++;
          } 
        }

        if(cont == dados.p || dados.e == dados.elementos ) {
          tempo = time(NULL) - tempo;
          fprintf(arq3, "%d", tempo);
          fclose(arq3);
          //dados.n++;          
          pthread_exit(NULL);
        }
      }
    }
  }
  tempo = time(NULL) - tempo;
  fprintf(arq3, "%d", tempo);
  fclose(arq3);
  //dados.n++;  
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

  N = (linhaA*colunaB) / p;  
  if( (linhaA*colunaB) % p != 0 ){
    N++;
    dados.resto = (linhaA*colunaB) % p;
  }
  dados.N = N;
    
  thread = malloc (N * sizeof(pthread_t));
  
  int TEMPO = time(NULL);

  for( int i=0 ; i < N; i++) {

    //printf ( " Processo principal criando thread #%d \n " , i ) ;
    status = pthread_create (&thread[i], NULL ,funcao_thread, (void*)(size_t)i) ;

    if(status != 0)
    {
      printf("Erro na criacao da thread. Codigo de Erro:%d\n", status);
      return 1;
    }

	}

  for(int i=0 ; i < N ; i++)
  {
    //printf ( "Esperando Thread %d finalizar .... \n" , i ) ;
    pthread_join ( thread [ i ] , &thread_return ) ;
    //printf ( "Thread %d finalizada \n" , i ) ;
  }

  //printf ( "processo vai finalizar \n" ) ;
  
  TEMPO = time(NULL) - TEMPO;
  printf("TEMPO = %d\n", TEMPO);

  fclose(arq);
  fclose(arq2);
  //fclose(arq3);

  //liberar memória
  temp = NULL;
  thread = NULL;
  dados.str = NULL;
  free(temp);
  free(thread);
  free(dados.str);

  // libera a memória das matrizes
  for (int i=0; i < linhaA; i++){
    dados.matrizA[i] = NULL;
    free (dados.matrizA[i]) ;
  }
  dados.matrizA = NULL;
  free (dados.matrizA) ;

  for (int i=0; i < linhaB; i++){
    dados.matrizB[i] = NULL;
    free (dados.matrizB[i]) ;
  }
  dados.matrizB = NULL;
  free (dados.matrizB) ;

  return 0;
}