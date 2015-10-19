#include "ABB.h"

#define campoChave matricula

typedef int tipoChave;

#define mascaraChave " %i; "

typedef  struct { 
    tipoChave campoChave;
    int idade;
    char nome[30];	
} info;

typedef  struct 
{
 int cod;
 char nome[30];
 char end[30];
 char fone[20];
}Agenda;



unsigned short  comparaCamposChaves1(void *pInfo1, void *pInfo2);
unsigned short  comparaCamposChaves2(void *chave, void *pInfo);
void exibeChave(void *pInfo);
void flush(FILE *in);
void menu(pABB p);
