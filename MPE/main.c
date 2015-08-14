#include "TDA_MpE_PRIV.h"


int main()
{

    pMP p;
    int consultado;
    int removido;
    int novoItem;

    int n=4;
    int l=3;
    int tamInfo = sizeof(int);

    cria(&p,n,l,tamInfo);

    novoItem = 5;

    insereNaPilha(p,2, &novoItem);

    consultaTopo(p, 2, &consultado);
    
    printf(">>TOPO: %d\n", consultado);

    removeDaPilha(p, 2, &removido);
    
    printf(">>REMOVEU: %d", removido);
    
    consultaTopo(p, 2, &consultado);
    
    destroi(&p);
    
    return 0;
}
