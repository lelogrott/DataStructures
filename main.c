#include "TDA_MpE_PRIV.h"


int main()
{

    ppMP pp;
    NoMP *consultado;
    int novoItem;

    int n=3;
    int l=4;
    int tamInfo = sizeof(int);

    cria(pp,n,l,tamInfo);

    novoItem = 5;

    insereNaPilha(*pp,2, &novoItem);
    printf("\ninseriu\n");
    consultaTopo(*pp, 2, consultado);


    return 0;
}
