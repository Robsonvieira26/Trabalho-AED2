#include "arvoreB.h"
#include "tad.c"
#include <stdio.h>
#include <stdlib.h>

/*
Grupo ALR
Integrantes:
Aristeu Alves Ferreira Neto - 11911BCC027
Loredana Romano Devico - 11911BCC001
Robson Roberto Vieira Junior - 11911BCC056
*/

int main() {
  ArvB *raiz;
  for (;;) {
    int op = menu();
    printf("sua escolha foi %d\n", op);
    switch (op) {
    case 1:
      raiz = criaArvB();
      printf("Arvore Iniciada\n");
      espera();
      break;
    case 2:
      printf("Digite o valor a ser Inserido:\n");
      espera();
      break;
    case 3:
      printf("Digite o valor a ser Removido:\n");
      espera();
      break;
    case 4:
      printf("Digite o valor a ser Procurado:\n");
      espera();
      break;
    case 5:
      printf("A quantidade Total de nos na arvore é: [VALOR]\n");
      espera();
      break;
    case 6:
      if (ehVaziaArvB(raiz) == 1)
        printf("A arvore esta vazia\n");
      else if (ehVaziaArvB(raiz) == 0)
        printf("A arvore nao esta vazia\n");
      else
        printf("A arvore nao iniciada\n");

      espera();
      break;
    case 7:
      printf("Arvore Apagada\n");
      espera();
      break;
    case 8:
      printf("Saindo...\n");
      exit(1);
      break;
    default:
      printf("Opcao Invalida");
      espera();
      break;
    }
  }
  return 0;
}
