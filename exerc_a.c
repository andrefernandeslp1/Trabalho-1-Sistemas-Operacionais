#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

void imprimir(int pid, int pid_pai)
{
  printf("Pid do PAI = %d , Pid Proprio = %d\n", pid_pai, pid);
}

int main(){
  pid_t filho1, filho2, neto1, neto2, pid, pai;

  pid = getpid();
  printf("Pai:\nPid Proprio = %d\n", pid);

  filho1 = fork();
  if (filho1 < 0)
  {
    printf("Erro ao criar processo\n");
    return 1;
  }
  if(filho1 == 0)
  {
    printf("Filho 1:\n");
    pid = getpid();
    pai = getppid();
    imprimir(pid, pai);

    neto1 = fork();
    if (neto1 == 0)
    {
      printf("Neto 1:\n");
      pid = getpid();
      pai = getppid();
      imprimir(pid, pai);
    }
    wait(NULL);
  }
  wait(NULL);
  if(filho1 > 0)
  {
    filho2 = fork();
    if (filho2 == 0)
    {
      printf("Filho 2:\n");
      pid = getpid();
      pai = getppid();
      imprimir(pid, pai);

      neto2 = fork();
      if (neto2 == 0)
      {
        printf("Neto 2:\n");
        pid = getpid();
        pai = getppid();
        imprimir(pid, pai);
      }
      wait(NULL);
    }
    wait(NULL);
  }
  return 0;
}