#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCESSO 0
#define FRACASSO 1

typedef struct MP *pMP, **ppMP;

int cria(ppMP pp, int N, int L, int tamInfo);
int insereNaPilha(pMP p, int nPilha, void* novo);
int removeDaPilha(pMP p, int nPilha, void* removido);
int consultaTopo(pMP p, int nPilha, void* consultado);
