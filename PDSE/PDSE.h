#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "math.h"

#define FRACASSO 0
#define SUCESSO 1

#define NAO 0
#define SIM 1



typedef struct PDSE *pPDSE, **ppPDSE;

int cria(ppPDSE pp, int tamInfo);

/*************** EMPILHA NO TOPO A PARTIR DO ENDEREÇO FORNECIDO PELO O CHAMADOR **************/
int insere(pPDSE p, void *novo);

//int tamanho(pPDSE p);

/*************** RETORNA A PILHA À CONDIÇÃO "VAZIA" **************/
int reinicia(pPDSE p);


int testaSeVazia(pPDSE p);

void destroi(ppPDSE pp);

/*************** BUSCA NO TOPO E COPIA ITEM P/ O CHAMADOR **************/
int busca(pPDSE p, void *reg);

/*************** DESEMPILHA E COPIA ITEM REMOVIDO P/ O CHAMADOR **************/
int removeTopo(pPDSE p, void *reg);

//int enderecosFisicos(pPDSE p);
