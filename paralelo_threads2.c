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
} dados;

pthread_t *thread;
int status;
void * thread_return;

void * incrementar(int *vetor, int i, int tempo)
{
  //vetor[2] += 1;  // n na função

  int incremento_x, incremento_y;

  incremento_x = dados.p / dados.colunaB;
  incremento_y = dados.p % dados.colunaB;

  FILE *arq4;
  char str_[50];
  vetor[0] += incremento_x; // i na função
  vetor[1] += incremento_y; // j na função
  if(vetor[1] >=dados.colunaB){
    vetor[0] += 1;
    vetor[1] = 0;
  }  
  tempo = time(NULL) - tempo;
  sprintf(str_, "matrizes_threads/matriz_C%d.txt", i+1);
  arq4 = fopen(str_, "a");
  fprintf(arq4, "%d", tempo);
  fclose(arq4); 
}

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

  int tempo = time(NULL);
  int cont=0;
  double aux;
  FILE *arq3;
  char str[50];

  int * v = (int*)vector;
  int i = v[0], j=v[1], n=v[2];

  printf("i = %d - j = %d - n = %d\n", i, j, n);

  for( i; i < dados.linhaA; ) {
    for( j; j < dados.colunaB; ) {

      if(dados.e < dados.elementos){

        aux = 0;
        //printf("%d\n", dados.e);
        //sleep(1);

        printf("TESTE\n");

        if(cont == 0) {        
          sprintf(str, "matrizes_threads/matriz_C%d.txt", n);
          arq3 = fopen(str, "w");
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

  //FILE *arq4;
  //char str_[50];
  
  int vetor[3] = {0,0,0};
  int incremento_x, incremento_y;

  incremento_x = p / colunaB;
  incremento_y = p % colunaB;
  
  //if(p % colunaB != 0)
    //incremento_x++;
  
  tempo = time(NULL);

  for( int i=0 ; i < N; i++) {
    

    //incrementar(vetor, i, tempo);

    //printf ( " Processo principal criando thread #%d \n " , i ) ;
    status = pthread_create (&thread[i], NULL ,funcao_thread, (void*)(size_t)vetor) ;
    //////////

    //vetor[2] += 1;  // n na função
    
    
    //*******
    //pthread_join ( thread [ i ] , &thread_return ) ;
    //printf("vetor[0] = %d - vetor[1] = %d - vetor[2] = %d\n", vetor[0], vetor[1], vetor[2]);  
    /*
    if(i < N)
    {
      vetor[0] += incremento_x; // i na função
      vetor[1] += incremento_y; // j na função
      if(vetor[1] >=colunaB){
        vetor[0] += 1;
        vetor[1] = 0;
      }  
      tempo = time(NULL) - tempo;
      sprintf(str_, "matrizes_threads/matriz_C%d.txt", i+1);
      arq4 = fopen(str_, "a");
      fprintf(arq4, "%d", tempo);
      fclose(arq4);
    }
    */
    
  }

  for(int i=0 ; i < N ; i++){
    //***************
    pthread_join ( thread[i] , &thread_return ) ;
    //******************
  }

  printf("Tempo = %ld", time(NULL) - tempo);

  //printf ( "processo vai finalizar \n" ) ;
  
  fclose(arq);
  fclose(arq2);
  //fclose(arq3);

  //liberar memória
  temp = NULL;
  thread = NULL;
  free(temp);
  free(thread);

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