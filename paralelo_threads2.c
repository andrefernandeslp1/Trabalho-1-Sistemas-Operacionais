#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

//comando: ./<programa> <matriz_1> <matriz_2> <quantidade_de_P_elementos>

struct Dados{
  int i, j, linhaA, linhaB, colunaA, colunaB, e, elementos, N, n, p;
  double **matrizA, **matrizB;
  char *str;
  int *tid;
} dados;

pthread_t *thread;
int status;
void * thread_return;

void * funcao_thread(void * vector)
{
  /*
  if ((int)(size_t)tid > 0){
    pthread_join (thread[(size_t)tid - 1], &thread_return) ; //espera a thread especificada terminar
    printf ("Esta é a Thread %d. A Thread %d terminou.\n", (int)(size_t)tid, (int)(size_t)tid - 1);
  }
  else
    printf ("Esta é a PRIMEIRA Thread.\n"); 
  */

  //int tempo = time(NULL);
  int cont=0;
  double aux;
  FILE *arq3;

  int * v = (int*)vector;
  int i = v[0], j=v[1];

  printf("ii = %d , jj = %d\n", i, j);

  for( i; i < dados.linhaA; ) {
    for( j; j < dados.colunaB; ) {

      if(dados.e < dados.elementos){

        aux = 0;
        //printf("%d\n", dados.e);
        //sleep(1);

        if(cont == 0) {        
          sprintf(dados.str, "matrizes_threads/matriz_C%d.txt", dados.n);
          arq3 = fopen(dados.str, "w");
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
          //tempo = time(NULL) - tempo;
          //fprintf(arq3, "%d", tempo);
          fclose(arq3);
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

  N = (linhaA*colunaB)/p;  
  if( (linhaA*colunaB) % p != 0 ) 
    N++;
    
  thread = malloc (N * sizeof(pthread_t));

  FILE *arq4;
  
  int vetor[2] = {0,0};
  int *ii, *jj, incremento_x, incremento_y;
  ii = &vetor[0];
  jj = &vetor[1];

  incremento_x = p / colunaB;
  incremento_y = p % colunaB;
  
  //if(p % colunaB != 0)
    //incremento_x++;

  for( int i=0 ; i < N; i++) {
    tempo = time(NULL);

    //printf ( " Processo principal criando thread #%d \n " , i ) ;
    status = pthread_create (&thread[i], NULL ,funcao_thread, (void*)(size_t)vetor) ;

    if(status != 0)
    {
      printf("Erro na criacao da thread. Codigo de Erro:%d\n", status);
      return 1;
    }

    dados.n++;
    
    //printf ( "Esperando Thread %d finalizar .... \n" , i ) ;
    pthread_join ( thread [ i ] , &thread_return ) ;
    //printf ( "Thread %d finalizada \n" , i ) ;
    
    vetor[0] += incremento_x;
    vetor[1] += incremento_y;
    if(vetor[1] >=colunaB){
      vetor[0] += 1;
      vetor[1] = 0;
    }

    printf("vetor[0] = %d - ", vetor[0]);
    printf("vetor[1] = %d\n", vetor[1]);

    tempo = time(NULL) - tempo;
    //printf("dados.str = %s\n", dados.str);
    arq4 = fopen(dados.str, "a");
    fprintf(arq4, "%d", tempo);
    fclose(arq4);
	}

  //printf ( "processo vai finalizar \n" ) ;
  
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