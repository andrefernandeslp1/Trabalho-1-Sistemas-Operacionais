#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
  int linhaA, linhaB, colunaA, colunaB, linhaC, colunaC, tempo;
  double aux;
  char *temp;

  FILE *arq, *arq2, *arq3;
  arq = fopen(argv[1], "r");
  arq2 = fopen(argv[2], "r");
  arq3 = fopen("matriz_3.txt", "w");

  fscanf(arq, "%d %d", &linhaA, &colunaA);
  fscanf(arq2, "%d %d", &linhaB, &colunaB);

  double **matrizA, **matrizB, **matrizC ;

  // aloca um vetor de LIN ponteiros para linhas
  matrizA = malloc (linhaA * sizeof (double*)) ;
  matrizB = malloc (linhaB * sizeof (double*)) ;
  matrizC = malloc (linhaA * sizeof (double*)) ;

  // aloca cada uma das linhas
  for (int i=0; i < linhaA; i++)
    matrizA[i] = malloc (colunaA * sizeof (double)) ;
  for (int i=0; i < linhaB; i++)
    matrizB[i] = malloc (colunaB * sizeof (double)) ;
  for (int i=0; i < linhaB; i++)
    matrizC[i] = malloc (colunaB * sizeof (double)) ;

  // percorre as matrizes
  for (int i=0; i < linhaA; i++)
    for (int j=0; j < colunaA; j++)
      fscanf(arq, "%s %lf", temp, &matrizA[i][j]);
  for (int i=0; i < linhaB; i++)
    for (int j=0; j < colunaB; j++)
      fscanf(arq2, "%s %lf", temp, &matrizB[i][j]);
      
  /*
  // imprime as matrizes
  printf("Matriz 1\n");
  for(int i = 0; i < linhaA; i++) {
		for(int j = 0; j < colunaA; j++) {      
			printf("%7.3lf", matrizA[i][j]);
		}
    printf("\n");
  }
  printf("Matriz 2\n");
  for(int i = 0; i < linhaB; i++) {
		for(int j = 0; j < colunaB; j++) {      
			printf("%7.3lf", matrizB[i][j]);
		}
    printf("\n");
  }
  */

  //multiplicação das matrizes
  tempo = time(NULL);
  for(int i = 0; i < linhaA; i++) {
    for(int j = 0; j < colunaB; j++) {
      
      for(int k = 0; k < linhaB; k++) {
        //printf("%d%dx%d%d + ", i,k,k,j);
        aux += matrizA[i][k] * matrizB[k][j];
      }
      //printf("\n");
      matrizC[i][j] = aux;
      aux = 0;
    }
	}
  tempo = time(NULL) - tempo;

  /*
  //imprime matriz 3
	printf("Matriz 3\n");
	for(int i = 0; i < linhaA; i++) {
		for(int j = 0; j < colunaB; j++) {
			printf("%7.3lf", matrizC[i][j]);
		}
		printf("\n");
	}
  */

  //grava matriz 3 em arquivo
  fprintf(arq3, "%d %d\n", linhaA, colunaB);
	for(int i = 0; i < linhaA; i++) {
		for(int j = 0; j < colunaB; j++) {
			fprintf(arq3, "c(%d,%d) %.3lf\n", i+1, j+1, matrizC[i][j]);
		}
	}
  fprintf(arq3, "%d", tempo);
  
  fclose(arq);
  fclose(arq2);
  fclose(arq3);

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
  

  for (int i=0; i < linhaA; i++){
    matrizC[i] = NULL;
    free (matrizC[i]) ;
  }
  matrizC = NULL;
  free (matrizC) ;
  
 return 0;
}