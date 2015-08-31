#include "PDSE_priv.h"

/*************** CRIA ***************/
int cria(ppPDSE pp, int tamInfo)
{   int ret = FRACASSO;
	if(((*pp)=(pPDSE)malloc(sizeof(PDSE)))==NULL)
		ret = FRACASSO;
	else
	{	(*pp)->topo=NULL;
        (*pp)->tamInfo=tamInfo;
        ret = SUCESSO;
	}
    return ret;
}

/*************** INSERE ***************/
int insere(pPDSE p, void *novo)
{  pNoPDSE temp;
   int ret = FRACASSO;
   if((temp=(NoPDSE *)malloc(sizeof(NoPDSE)))!=NULL)
   { if((temp->dados = (void *) malloc(p->tamInfo)) !=NULL )
     {   memcpy(temp->dados,novo,p->tamInfo);
 		 temp->abaixo=p->topo;
         p->topo=temp;
         ret = SUCESSO;
     }
     else
       free(temp);
	}
   return ret;
}


/*************** REMOVE E COPIA ITEM REMOVIDO P/ O CHAMADOR **************/
int removeTopo(pPDSE p, void *reg)
{  int ret = FRACASSO;
    pNoPDSE aux=NULL;
	if(p->topo != NULL)
	{ aux=p->topo->abaixo;
	  memcpy(reg,p->topo->dados,p->tamInfo);
      free(p->topo->dados);
      free(p->topo);
	  p->topo=aux;
      ret = SUCESSO;
	}
   return ret;
}



/*************** BUSCA ***************/
int busca(pPDSE p, void *reg)
{  int ret = FRACASSO;
   if(p->topo != NULL)
	{ memcpy(reg,p->topo->dados,p->tamInfo);
      ret = SUCESSO;
	}
   return ret;
}


int testaSeVazia(pPDSE p)
{    if(p->topo != NULL)
        return NAO;
     else
        return SIM;
}


/*************** PURGA ***************/
int reinicia(pPDSE p)
{	pNoPDSE aux=NULL;

    if(p->topo != NULL)
	{	aux=p->topo->abaixo;

	    while(aux != NULL)
		{
            free(p->topo->dados);
		 	free(p->topo);
		 	p->topo=aux;
		 	aux=p->topo->abaixo;
		}
	   free(p->topo->dados);
       free(p->topo);
       p->topo = NULL;
	}
	return SUCESSO;
}

/*************** DESTROI ***************/
void destroi(ppPDSE pp)
{
	reinicia(*pp);
	free(*pp);
   (*pp)=NULL;
}
/*************** INVERTE ***************/
int inverte(pPDSE p)
{
    pNoPDSE aux, aux2;
    int cont=0;
    aux=p->topo;
     
    while(aux!=NULL)//conta elementos da pilha
    {
        cont++;
        aux = aux->abaixo;
    }

    int iteracoes = cont-1;

    for(cont=1;cont<=iteracoes;cont++)
    {
        int pulos=cont;
        aux=p->topo;
        aux2=aux;
        while(pulos--)
        {
            aux=aux->abaixo;
            if(pulos)
                aux2=aux2->abaixo;
        }
        aux2->abaixo=aux->abaixo;
        aux->abaixo=p->topo;
        p->topo=aux;
    }
    

    return SUCESSO;
}
/*************** MOSTRA PILHA **********/
int mostraPilha(pPDSE p, void (*mostraDado)(void*))
{  
    pNoPDSE aux;
    aux=p->topo;
    int ret = FRACASSO;
     
    while(aux!=NULL)
    {
        mostraDado(aux->dados);
        aux = aux->abaixo;
    }
    ret = SUCESSO;

   return ret;
}
/***************GERA PILHA************/
int geraPilha(pPDSE p, int nElementos)
{
    int i;
    for(i=0;i<nElementos;i++)
    {
        insere(p, &i);
    }
    return SUCESSO;
}
