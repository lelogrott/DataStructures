#include "TDA_MpE_PRIV.h"


int main()
{

    pMP p;
    NoMP *consultado;
    int novoItem;

    int n=3;
    int l=4;
    int tamInfo = sizeof(int);

    cria(&p,n,l,tamInfo);

    novoItem = 5;

    insereNaPilha(p,2, &novoItem);
    printf("\ninseriu\n");
    consultaTopo(p, 2, consultado);


    return 0;
}
