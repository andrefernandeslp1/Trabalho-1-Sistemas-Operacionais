#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

//comando: ./<programa> <matriz_1> <matriz_2> <numero inteiro>

int main (int argc, char *argv[])
{
  int linhaA, linhaB, colunaA, colunaB, linhaC, colunaC, cont, N, n=0, tempo, p;
  double aux;
  char *temp, *str, *str2;

  FILE *arq, *arq2, *arq3;
  arq = fopen(argv[1], "r");
  arq2 = fopen(argv[2], "r");
  p = atoi(argv[3]);
  fscanf(arq, "%d %d", &linhaA, &colunaA);
  fscanf(arq2, "%d %d", &linhaB, &colunaB);

  N = (linhaA*colunaB)/p;  

  double **matrizA, **matrizB, **matrizC ;

  // aloca um vetor de LIN ponteiros para linhas
  matrizA = malloc (linhaA * sizeof (double*)) ;
  matrizB = malloc (linhaB * sizeof (double*)) ;
  matrizC = malloc (linhaA * sizeof (double*)) ;
  str = malloc (sizeof(char));

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

  //multiplicação das matrizes
  cont = 0;
  for(int i = 0; i < linhaA; i++) {
    for(int j = 0; j < colunaB; j++) {
      if(cont == 0)
      {        
        sprintf(str, "matrizes_threads/matriz_3.%d.txt", n);
        arq3 = fopen(str, "w");
        fprintf(arq3, "%d %d\n", linhaA, colunaB);
        tempo = time(NULL);
      }
      for(int k = 0; k < linhaB; k++) {
        aux += matrizA[i][k] * matrizB[k][j];
      }
      if(cont < p-1)
      {
        fprintf(arq3, "c(%d,%d) %.3lf\n", i+1, j+1, aux);
        cont++;
      }
      else
      {
        fprintf(arq3, "c(%d,%d) %.3lf\n", i+1, j+1, aux);
        tempo = time(NULL) - tempo;
        fprintf(arq3, "%d", tempo);
        fclose(arq3);
        cont = 0;
        n++;
      }
      aux = 0;
    }
	}
  
  fclose(arq);
  fclose(arq2);
  fclose(arq3);

  // libera a memória das matrizes
  for (int i=0; i < linhaA; i++)
    free (matrizA[i]) ;
  free (matrizA) ;

  for (int i=0; i < linhaB; i++)
    free (matrizB[i]) ;
  free (matrizB) ;

  for (int i=0; i < linhaA; i++)
    free (matrizC[i]) ;
  free (matrizC) ;
  
 return 0;
}