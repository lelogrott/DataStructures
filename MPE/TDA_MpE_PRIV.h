#include "TDA_MpE.h"

/* N� descritor da uma pilha */
typedef struct {
    short int topo;
    short int inicioParticao;
}DescPilha;

/* N� da Multi-Pilha */
typedef union {
    DescPilha descritor;
    void* dados;
}NoMP, *pNoMP;

/* Descritor da Multi-Pilha */
typedef struct MP{
    int N; /* N = N�mero de Pilhas*/
    int L; /* L = Tamanho m�ximo da parti��o de cada Pilha*/
    int tamInfo;
    pNoMP vet;
}MP, *pMP, **ppMP;
