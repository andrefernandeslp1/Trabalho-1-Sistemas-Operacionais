#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>

//comando: ./<programa> <matriz_1> <matriz_2> <numero inteiro>

typedef struct{
  int i, j, linhaA, linhaB, colunaA, colunaB, e, elementos, N, n, p;
  int tempo, ii;
  double **matrizA, **matrizB;
  char *str;
} Dados;

Dados * dados;

int funcao(Dados *dados)
{
  int cont=0;
  double aux;
  FILE *arq3;

  for( dados->i; dados->i < dados->linhaA; ) {
    for( dados->j; dados->j < dados->colunaB; ) {

      if(dados->e < dados->elementos){

        aux = 0;

        if(cont == 0) {        
          sprintf(dados->str, "matrizes_processos/matriz_C%d.txt", dados->n);
          //printf("dados->str = %s\n", dados->str);
          arq3 = fopen(dados->str, "w");
          fprintf(arq3, "%d %d\n", dados->linhaA, dados->colunaB);
        }
        
        for(int k = 0; k < dados->linhaB; k++) 
          aux += dados->matrizA[dados->i][k] * dados->matrizB[k][dados->j];

        if(cont < dados->p ) {
          fprintf(arq3, "c(%d,%d) %.3lf\n", dados->i+1, dados->j+1, aux);
          dados->e++;
          cont++;
          if(dados->j < dados->colunaB - 1) {
            dados->j++;
          }
          else {
            dados->j = 0;
            dados->i++;
          } 
        }

        if(cont == dados->p || dados->e == dados->elementos ) {
          fclose(arq3);
          return 0;
        }
      }
    }
  }
  fclose(arq3);
  return 0;
}

int main (int argc, char *argv[])
{
  int valor = shmget ( IPC_PRIVATE , sizeof ( Dados ) , IPC_CREAT | 0666 ) ;
  Dados *dados = (Dados*) shmat (valor, NULL, 0);
  
  if(valor < 0){
    printf("Erro na alocacao!\n");
    return 1;
  }

  int filho, linhaA, linhaB, colunaA, colunaB, linhaC, colunaC, cont, elementos, N, n=0, p;
  char *temp;
  temp = malloc(sizeof(char));

  FILE *arq, *arq2, *arq4;
  arq = fopen(argv[1], "r");
  arq2 = fopen(argv[2], "r");
  p = atoi(argv[3]);
  fscanf(arq, "%d %d", &linhaA, &colunaA);
  fscanf(arq2, "%d %d", &linhaB, &colunaB);  

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

  // percorre as matrizes
  for (int i=0; i < linhaA; i++)
    for (int j=0; j < colunaA; j++)
      fscanf(arq, "%s %lf", temp, &dados->matrizA[i][j]);
  for (int i=0; i < linhaB; i++)
    for (int j=0; j < colunaB; j++)
      fscanf(arq2, "%s %lf", temp, &dados->matrizB[i][j]);

  //struct recebe dados
  dados->linhaA = linhaA;
  dados->linhaB = linhaB;
  dados->colunaA = colunaA;
  dados->colunaB = colunaB;
  dados->p = p;
  dados->n = 0;
  dados->i = 0;
  dados->j = 0 ;  
  dados->e = 0;
  dados->elementos = (linhaA*colunaB);
  dados->ii = 0;

  N = (linhaA*colunaB)/p;  
  if( (linhaA*colunaB) % p != 0 ) 
    N++;

  dados->N = N;

  for( int i=0 ; i < dados->N; i++) {
    dados->tempo = time(NULL);
    
    filho = fork();

    if(filho == 0)
    {
      dados = shmat (valor, NULL, 0);
      //printf("Filho %d pid %d: \n", i, getpid());
      //printf("Filho %d pid_pai %d: \n", i, getppid());
      funcao(dados);
      
      shmdt(dados);
      exit(0);
    }
    wait(NULL);

    dados->tempo = time(NULL) - dados->tempo;
    //printf("time = %d\n", dados->tempo);
    sprintf(dados->str, "matrizes_processos/matriz_C%d.txt", dados->n);
    arq4 = fopen(dados->str, "a");
    fprintf(arq4, "%d", dados->tempo);
    fclose(arq4);

    dados->n++;
	}

  //printf ( "processo vai finalizar \n" ) ;
  
  fclose(arq);
  fclose(arq2);
  //fclose(arq3);

  //liberar memória
  temp = NULL;
  dados->str = NULL;
  free(temp);
  free(dados->str);

  // libera a memória das matrizes
  for (int i=0; i < linhaA; i++){
    dados->matrizA[i] = NULL;
    free (dados->matrizA[i]) ;
  }
  dados->matrizA = NULL;
  free (dados->matrizA) ;

  for (int i=0; i < linhaB; i++){
    dados->matrizB[i] = NULL;
    free (dados->matrizB[i]) ;
  }
  dados->matrizB = NULL;
  free (dados->matrizB) ;

  shmctl( valor , IPC_RMID , NULL );
  //exit(0);

  return 0;
}