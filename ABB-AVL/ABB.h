#include "stdio.h"
#include "stdlib.h"
#include "string.h"


#define SIM 1
#define NAO 0
#define MAIOR
#define MENOR
#define IGUAL
#define SUCESSO 1
#define FRACASSO 0

typedef struct ABB *pABB,**ppABB;



/*
opera��o de cria��o:
pr�-condi��o: a exist�ncia de um apontador adequadamente
declarado e passado por refer�ncia para a fun��o juntamente com
o tamanho (a quantidade de bytes) do tipo de informa��o a ser manipulada.
p�s-condi��o: a cria��o e inicializa��o do TDA ABB, atribui��o do seu endere�o ao
ponteiro passado por referencia. Na ocorr�ncia de algum problema durante a
cria��o retorna-se a macro FRACASSO, caso contr�rio retorna-se a macro SUCESSO.*/
int criaABB(ppABB pp, int tamInfo);

/*opera��o destrutora:
pr�-condi��o: a exist�ncia de um apontador declarado externamente a esta fun��o,
devidamente iniciado com o endere�o do TDA e cujo endere�o (deste apontador)
deve ser passado para a fun��o.
p�s-condi��o: a libera��o de qualquer regi�o de mem�ria utilizada pelo TDA
seguida da anula��o do ponteiro passado por referencia*/
void destroiABB(ppABB pp);

/* tipo de opera��o: fun��o de manipula��o.
pr� condi��o: a pr� exist�ncia do TDA cujo endere�o � passado para a fun��o.
p�s condi��o: esvaziamento dos dados, o TDA retorna ao estado apresentado
imediatamente ap�s a sua cria��o. */
void reiniciaABB(pABB p);

//void apagaNoABB(pNoABB p);

int buscaABB(pABB p, void *destino, void *chaveDeBusca, unsigned short (* cmp)(void *p1, void *p2));

int insereABB(pABB p, void *novoReg, unsigned short (* cmp)(void *p1, void *p2));

int removeABB(pABB p, void *chave, unsigned short (* cmp)(void *p1, void *p2), void *copia);

int testaVaziaABB(pABB);


void balancear(pABB p);


int numFolhas(pABB p);

int emOrdem(pABB pa, void (* processa)(void *p));

int emOrdemIterativa(pABB pa, void (* processa)(void *p));

int posOrdem(pABB pa, void (* processa)(void *p));

int preOrdem(pABB pa,  void (* processa)(void *p));

