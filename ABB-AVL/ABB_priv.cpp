#include "ABB_priv.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <iostream>
#include <stack>

using namespace std;

void apagaNoABB(pNoABB p)
{ if(p!=NULL)
   {   apagaNoABB(p->esq);
       apagaNoABB(p->dir);
       free( p->dados );
       free(p);
   }

}



void percorreEmPreOrdem(pNoABB p,  void (* processa)(void *p))
{  if(p != NULL)
    { processa(p->dados);
      percorreEmPreOrdem(p->esq, processa);
      percorreEmPreOrdem(p->dir, processa);
    }
}

void percorreEmOrdem(pNoABB p,  void (* processa)(void *p))
{  if(p != NULL)
    { percorreEmOrdem(p->esq, processa);
      processa(p->dados);
      percorreEmOrdem(p->dir, processa);
    }
}

void percorreEmPosOrdem(pNoABB p, void (* processa)(void *p))
{ if(p != NULL)
    { percorreEmPosOrdem(p->esq, processa);
      percorreEmPosOrdem(p->dir, processa);
      processa(p->dados);
    }
}

void percorreEmOrdemIterativa(pNoABB p,  void (* processa)(void *p))
{  

    stack<pNoABB> pilhaAux;
    /* set current to root of binary tree */
  pNoABB current = p;
  //struct sNode *s = NULL;  /* Initialize stack s */
  bool done = 0;
 
  while (!done)
  {
    /* Reach the left most tNode of the current tNode */
    if(current !=  NULL)
    {
      /* place pointer to a tree node on the stack before traversing 
        the node's left subtree */
      pilhaAux.push(current);                                               
      current = current->esq;  
    }
        
    /* backtrack from the empty subtree and visit the tNode 
       at the top of the stack; however, if the stack is empty,
      you are done */
    else                                                             
    {
      if (!pilhaAux.empty())
      {
        current = pilhaAux.top();
        processa(current->dados);
        pilhaAux.pop();
 
        /* we have visited the node and its left subtree.
          Now, it's right subtree's turn */
        current = current->dir;
      }
      else
        done = true; 
    }
  } /* end of while */ 

}

int calcNumFolhas(pNoABB p)
{   if(!p)
     return 0;
    else
     if(!(p->esq) && !(p->dir))
        return 1;
     else
        return calcNumFolhas(p->esq)+calcNumFolhas(p->dir);
}


