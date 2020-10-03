#include "arvoreB.h"
#include <stdio.h>
#include <stdlib.h>
#define GRAU 6

struct NO {
  int chaves[GRAU - 1], cont; // valores possiveis em um no && cont é a
                              // quantidade de valores nesse no
  struct NO *ptrFilhos[GRAU];
};

ArvB criaNO() {
  ArvB no = (ArvB)malloc(sizeof(struct NO));
  no->cont = 0;
  for (int i = 0; i < GRAU; i++) {
    no->ptrFilhos[i] = NULL;
  }
  return no;
}

ArvB *criaArvB() {
  ArvB *raiz = (ArvB *)malloc(sizeof(ArvB));
  if (raiz != NULL) {
    *raiz = criaNO();
  }

  return raiz;
}

void emOrdemArvB(ArvB *raiz) { // filho esq pai filho dir
  // Em ordem
  ArvB auxArvB = *raiz;
  int i;
  if (auxArvB != NULL) {
    for (i = 0; i < auxArvB->cont; i++) {
      emOrdemArvB(&(auxArvB->ptrFilhos[i]));
      printf("[%d]", auxArvB->chaves[i]);
    }
    emOrdemArvB(&(auxArvB->ptrFilhos[i]));
  }
}

int insereNo(ArvB *raiz, ArvB *pai, int valor) {

  if (ehVaziaArvB(raiz)) {
    return 0;
  }
  // percorre e insere no sem fazer split
  int i = 0;
  for (; i < (*raiz)->cont; i++) {
    if (valor <= (*raiz)->chaves[i]) {
      if (valor == (*raiz)->chaves[i])
        return 1;
      if (insereNo(&((*raiz)->ptrFilhos[i]), raiz, valor))
        break;
      // insere quando nao da pra inserir no no de baixo
      int j = (*raiz)->cont;
      while (j > i) {
        (*raiz)->chaves[j] = (*raiz)->chaves[j - 1];
        j--;
      }

      (*raiz)->chaves[i] = valor;
      (*raiz)->cont++;
      break;
    }
  }
  if (i == (*raiz)->cont) {
    if (!insereNo(&((*raiz)->ptrFilhos[i]), raiz, valor)) {
      (*raiz)->chaves[i] = valor;
      (*raiz)->cont++;
    }
  }
  // so faz split quando o no atual enche
  if (ehCheiaArvB(raiz)) {
    split(raiz, pai);
  }

  return 1;
}

int insereArvB(ArvB *raiz, int valor) { return insereNo(raiz, raiz, valor); }

void split(ArvB *raiz, ArvB *pai) {
  int max = (*raiz)->cont;
  int mediana = (max / 2);

  ArvB left = criaNO();
  ArvB right = criaNO();
  int l = 0;
  for (; l < mediana; l++) {
    left->chaves[l] = (*raiz)->chaves[l];
    left->cont++;
  }
  int k = 0;
  for (; k <= mediana; k++) {
    left->ptrFilhos[k] = (*raiz)->ptrFilhos[k];
  }

  l++;
  int j = 0;
  for (; l < max; l++) {
    right->chaves[j] = (*raiz)->chaves[l];
    right->ptrFilhos[j] = (*raiz)->ptrFilhos[l];
    right->cont++;
    j++;
  }
  j = 0;
  for (; k <= max; k++) {
    right->ptrFilhos[j] = (*raiz)->ptrFilhos[k];
    j++;
  }
  // promovendo o valor
  int promoverValor = (*raiz)->chaves[mediana];
  free(*raiz);
  *raiz = NULL;

  int t = 0;
  if ((*pai) == NULL) {
    (*pai) = criaNO();
  } else {
    for (; t < (*pai)->cont; t++) {
      if (promoverValor < (*pai)->chaves[t]) {

        int j = (*pai)->cont;
        while (j > t) {
          (*pai)->chaves[j] = (*pai)->chaves[j - 1];
          j--;
        }
        j = (*pai)->cont + 1;
        while (j > (t + 1)) {
          (*pai)->ptrFilhos[j] = (*pai)->ptrFilhos[j - 1];
          j--;
        }

        (*pai)->chaves[t] = promoverValor;
        (*pai)->ptrFilhos[t] = left;
        (*pai)->ptrFilhos[t + 1] = right;
        (*pai)->cont++;
        break;
      }
    }
  }
  if (t == (*pai)->cont) {
    (*pai)->chaves[t] = promoverValor;
    (*pai)->ptrFilhos[t] = left;
    (*pai)->ptrFilhos[t + 1] = right;
    (*pai)->cont++;
  }
}
// void liberaArvB(ArvB *raiz) {}
// int removeArvB(ArvB *raiz, int valor) {}

int buscaArvB(ArvB *raiz, int valor) {
  // Em ordem
  ArvB auxArvB = *raiz;
  int i, existeElemento = 0; // j quantidade de valores que foram testa no no
  if (auxArvB != NULL) {
    for (i = 0; i < auxArvB->cont; i++) {
      existeElemento =+ buscaArvB(&(auxArvB->ptrFilhos[i]), valor);
      if (auxArvB->chaves[i] == valor)
        return 1;
      // printf("\n [%d]\n", auxArvB->chaves[i]);
    }
    existeElemento =+ buscaArvB(&(auxArvB->ptrFilhos[i]), valor);
    if (auxArvB->chaves[i] == valor)
        return 1;
  }
  return existeElemento;
}

int totalNOArvB(ArvB *raiz) {
  if (ehVaziaArvB(raiz)) {
    return 0;
  }
  int i = 0, total = 1;
  for (i = 0; i <= (*raiz)->cont; i++) {
    total = total + totalNOArvB(&((*raiz)->ptrFilhos[i]));
  }
  return total;
}

int ehVaziaArvB(ArvB *raiz) {
  if (raiz == NULL) // raiz é null
    return 1;
  if (*raiz == NULL) // conteudo da raiz é null
    return 1;
  return 0;
}

int ehCheiaArvB(ArvB *raiz) {
  if (ehVaziaArvB(raiz)) {
    return 0;
  }
  if ((*raiz)->cont == (GRAU - 1)) {
    return 1;
  }
  return 0;
}

int menu() {
  int op;
  do {
    printf("==============================\n");
    printf("|        ARVORE B MENU       |\n");
    printf("|        GRAU %d              |\n", GRAU);
    printf("==============================\n");
    printf("|[1] Iniciar Arvore B        |\n");
    printf("|[2] Inserir um Valor        |\n");
    printf("|[3] Remover um Valor        |\n");
    printf("|[4] Procurar um Valor       |\n");
    printf("|[5] Total de Nos            |\n");
    printf("|[6] Arvore Vazia?           |\n");
    printf("|[7] Imprimir                |\n");
    printf("|[8] Apagar                  |\n");
    printf("|[9] Sair do Programa        |\n");
    printf("------------------------------\n");
    printf("|[O] Escolha: ");
    scanf("%d", &op);
    printf("------------------------------\n");
  } while (op < 0 || op > 9);
  return op;
}
void espera() {
  system("pause");
  system("cls");
}