#include "ABB.h"
#include "ABB_priv.h"
#include "math.h"



int criaABB(ppABB pp, int tamInfo)
{  int ret = FRACASSO;
   if ((*pp = (pABB) malloc(sizeof(ABB))) != NULL )
      {	(*pp)->raiz = NULL;
	(*pp)->tamInfo = tamInfo;
	ret = SUCESSO;
      }
	return ret;
}


void destroiABB(ppABB pp)
{  reiniciaABB(*pp);
   free(*pp);
   (*pp)= NULL;
}


void reiniciaABB(pABB p)
{
   apagaNoABB(p->raiz);
   p->raiz = NULL;
}

int buscaABB(pABB pa, void *destino, void *chaveDeBusca, unsigned short(* cmp)(void *p1, void *p2))
{  pNoABB aux;
   unsigned int ret= FRACASSO;
   aux = pa->raiz;
   while( aux != NULL && (*cmp)(chaveDeBusca,aux->dados) != '=')
          aux = (*cmp)(chaveDeBusca,aux->dados)== '<' ? aux->esq : aux->dir;
   if (aux != NULL)
    {   memcpy(destino, aux->dados, pa->tamInfo);
        ret = SUCESSO;
    }
   return ret;
}


int insereABB(pABB pa, void *novoReg, unsigned short (* cmp)(void *p1, void *p2))
{  	
    pNoABB p, q, novoNoABB;

    p = q = pa->raiz;
    while( p != NULL )
    {
        if ( (*cmp)(novoReg,p->dados) == '=')
            return FRACASSO;  /* registro j� inserido previamente */
        else
        {
            q = p;
            p = ((*cmp)(novoReg,p->dados)== '<') ? p->esq : p->dir;
        }
    }

    if ((novoNoABB = (pNoABB) malloc (sizeof(NoABB))) != NULL)
    {
        if((novoNoABB->dados = (void *)malloc(pa->tamInfo)) !=NULL)
        {
            memcpy(novoNoABB->dados, novoReg, pa->tamInfo);
            novoNoABB->dir = novoNoABB->esq = NULL; /* insere nova folha */

            if (q != NULL)
                if( (*cmp)(novoNoABB->dados,q->dados) == '<')/*ou (*cmp)(novoReg,q->dados)*/
                    q->esq = novoNoABB;
                else
                    q->dir=novoNoABB;
                else
                    pa->raiz = novoNoABB;   /* �rvore com um �nico n� */
            balancear(pa);printf(">chamou balancear\n");
            return SUCESSO;
        }
        else
            free(novoNoABB);
    }
    return FRACASSO;  /* n�o conseguiu alocar mem�ria */
}


int removeABB(pABB pa, void *chaveDeBusca, unsigned short (* cmp)(void *p1, void *p2), void *copia)
{	char ch;
	pNoABB subst, paiSubst, alvo, paiDoAlvo, avante;
   	paiDoAlvo = NULL;
	alvo = pa->raiz;
   	while (alvo != NULL && (ch=(*cmp)(chaveDeBusca,alvo->dados)) != '=')
	{	paiDoAlvo = alvo;
  		alvo = (ch == '<' ? alvo->esq : alvo->dir);
	}

   	if (alvo==NULL)   /*alvo n�o encontrado */
		return FRACASSO;

	if (alvo->esq == NULL)
		if (alvo->dir == NULL) // alvo � uma folha
			subst = NULL;
		else
			subst = alvo->dir; /*alvo possui apenas um filho � dir*/

	else 	
		if(alvo->dir == NULL)
			subst = alvo->esq; /*alvo possui apenas um filho � esq*/

		else  /* alvo possui os dois filhos*/
		{    	/* determinando o substituto pelo sucessor em ordem: */	
			paiSubst = alvo;
		     	subst = alvo->dir;
		     	avante = alvo->esq;
		     	while( avante != NULL)
                	{   paiSubst = subst;
	                    subst = avante;
        	            avante = avante->esq;
        	        }


			if(paiSubst != alvo)
	 	        {  	paiSubst->esq = subst->dir;
				subst->dir = alvo->dir;
 		        }
 		     	subst->esq = alvo->esq; /*o pai do substituto eh o proprio alvo */
	    }

	 if(pa->raiz == alvo) // ou seja se "paiDoAlvo = NULL"
       		pa->raiz = subst; /*alvo era a raiz*/
	 else
	    	alvo == paiDoAlvo->esq ? (paiDoAlvo->esq = subst) : (paiDoAlvo->dir = subst);
    	
	memcpy(copia,alvo->dados,pa->tamInfo);
    	free(alvo->dados);
	free(alvo);
	return SUCESSO;
}


int testaVaziaABB(pABB p)
{ return (p->raiz == NULL ? SIM : NAO);
}


int preOrdem(pABB pa, void (* processa)(void *p))
{   if(pa->raiz == NULL)
        return FRACASSO;
    else
    {
        percorreEmPreOrdem(pa->raiz, processa);
        return SUCESSO;
    }

}

int posOrdem(pABB pa, void (* processa)(void *p))
{   if(pa->raiz == NULL)
        return FRACASSO;
    else
    {
        percorreEmPosOrdem(pa->raiz, processa);
        return SUCESSO;
    }

}

int emOrdem(pABB pa,  void (* processa)(void *p))
{   if(pa->raiz == NULL)
        return FRACASSO;
    else
     {  percorreEmOrdem(pa->raiz, processa);
        return SUCESSO;
     }

}

int emOrdemIterativa(pABB pa,  void (* processa)(void *p))
{   if(pa->raiz == NULL)
        return FRACASSO;
    else
     {  percorreEmOrdemIterativa(pa->raiz, processa);
        return SUCESSO;
     }

}



int numFolhas(pABB p)
{   if(p!=NULL)
        return calcNumFolhas(p->raiz);
    return 0;
}


/* encontra a altura do n� recursivamente */

int alturaNo( pNoABB no ) {
	int altura_esquerda = 0;
	int altura_direita = 0;
    if(no==NULL)
        return 1;
	if( no->esq !=NULL)
	    altura_esquerda = alturaNo( no->esq );
	if( no->dir !=NULL)
	    altura_direita = alturaNo( no->dir );

	return altura_direita > altura_esquerda ? ++altura_direita : ++altura_esquerda;
}

/****calcula fator de balanceamento ******/
int fator_balanceamento( pNoABB no ) {
	/*int bf = 0;
    
	if(no->esq != NULL) bf += 1+fator_balanceamento( no->esq );
	if(no->dir != NULL) bf -= 1+fator_balanceamento( no->dir );

	return bf ;*/
	if (no == NULL)
        return 0;
    return alturaNo(no->esq) - alturaNo(no->dir);
}

/* Rota��o LL */
pNoABB rotacao_LL( pNoABB no) {
 	pNoABB a = no;
	pNoABB b = a->esq;
	
	a->esq = b->dir;
	b->dir = a;

	return(b);
}


/* Rota��o LR*/
pNoABB rotacao_LR(pNoABB no) {
	pNoABB a = no;
	pNoABB b = a->esq;
	pNoABB c = b->dir;
	
	a->esq = c->dir;
	b->dir = c->esq; 
	c->esq = b;
	c->dir = a;

	return(c);
}

/* Rota��o RL*/
pNoABB rotacao_RL(pNoABB no) {
	pNoABB a = no;
	pNoABB b = a->dir;
	pNoABB c = b->esq;
	
	a->dir = c->esq;
	b->esq = c->dir; 
	c->dir = b;
	c->esq = a;

	return(c);
}

/* Rota��o RR */
pNoABB rotacao_RR(pNoABB no) {
	pNoABB a = no;
	pNoABB b = a->dir;
	
	a->dir = b->esq;
	b->esq = a; 

	return( b );
}

/* Balancear n� dado*/
pNoABB balancear_no(pNoABB no) {
	pNoABB novaRaiz = NULL; printf(">entrou balancear\n");

	/* Balancear os filhos, se existirem */
	if( no->esq !=NULL)
		no->esq  = balancear_no( no->esq  );
	if( no->dir !=NULL ) 
		no->dir = balancear_no( no->dir );

	int bf = fator_balanceamento(no);
printf("@@@@@ %d\n", bf);
	if( bf >= 2 ) {
		/* esquerda pesada */	

		if( fator_balanceamento( no->esq ) <= -1 ) 
			novaRaiz = rotacao_LR(no);
		else 
			novaRaiz = rotacao_LL(no);

	} else if( bf <= -2 ) {
		/*Direita pesada*/

		if( fator_balanceamento(no->dir) >= 1 )
			novaRaiz = rotacao_RL(no);
		else 
			novaRaiz = rotacao_RR(no);

	} else {
		/* Este n� est� balanceado, sem mudan�as */

		novaRaiz = no;
	}

	return(novaRaiz);	
}

/* Balancear �rvore */
void balancear(pABB p) {

	pNoABB novaRaiz = NULL;

	novaRaiz = balancear_no( p->raiz );

	if( novaRaiz != p->raiz )  {
		p->raiz = novaRaiz; 
	}
	return;
}


