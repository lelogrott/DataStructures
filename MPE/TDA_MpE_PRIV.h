#include "TDA_MpE.h"

/* Nó descritor da uma pilha */
typedef struct {
    short int topo;
    short int inicioParticao;
}DescPilha;

/* Nó da Multi-Pilha */
typedef union {
    DescPilha descritor;
    void* dados;
}NoMP, *pNoMP;

/* Descritor da Multi-Pilha */
typedef struct MP{
    int N; /* N = Número de Pilhas*/
    int L; /* L = Tamanho máximo da partição de cada Pilha*/
    int tamInfo;
    pNoMP vet;
}MP, *pMP, **ppMP;
