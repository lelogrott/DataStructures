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

    insereNaPilha(p,4, &novoItem);

    consultaTopo(p, 4, &consultado);
    
    printf(">>TOPO: %d\n", consultado);

    removeDaPilha(p, 4, &removido);
    
    printf(">>REMOVEU: %d", removido);
    
    consultaTopo(p, 4, &consultado);
    
    destroi(&p);
    
    return 0;
}
