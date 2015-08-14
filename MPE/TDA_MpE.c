#include "TDA_MpE_PRIV.h"

int cria( ppMP pp, int N, int L, int tamInfo)
{
    int i, M, ret = SUCESSO;
    pNoMP aux;
    if (N > 0 && L > 0 && tamInfo > 0)
    {
        M = N*L;
        if((*pp = (pMP) malloc(sizeof(MP)))==NULL) /* criação do descritor geral da MpE; */
            ret = FRACASSO;
        else
            if( ( (*pp)->vet = (pNoMP) malloc((M+N)* sizeof(NoMP)) )==NULL)
            { /* Alocação de memória para a multipilha (vetor de unions) constituida de N*L nós de dados (N*L = M) e os N nós descritores das respectivas pilhas; */

                free (*pp);
                (*pp) = NULL;
                ret = FRACASSO;
            }
            else
            {
                (*pp)->N = N; /* Iniciando os atributos gerais da multi-pilha; */
                (*pp)->L = L;
                (*pp)->tamInfo = tamInfo;
                aux= (*pp)->vet; /* Ponteiro auxiliar aux apontando para a área de descritores; */
                for(i = 0; i < N ; i++) /* Formatando a MpE: iniciando os descritores das pilhas; */
                {
                    (aux+ i)->descritor.topo = -1;
                    /* Os topos são iniciados com valores que não indexam as partições das respectivas pilhas,
                    indicando que a considerada pilha está vazia. Perceba que também é possível utilizar a
                    sintaxe (*pp)->vet[i].descritor ou ((*pp)->vet + i).descritor para acesso ao i-ésimo
                    descritor. */
                    (aux+ i)->descritor.inicioParticao = N + i*L;
                }
                aux = aux + N; /* Ponteiro auxiliar aux apontando para o início da área de dados; */
                for(i = 0; i < M ;i++) /* Criando as áreas de dados */
                    if (((aux+i)->dados = (void*) malloc(tamInfo)) == NULL )
                    {
                        for(--i; i >=0;--i)
                            free((*pp)->vet[i].dados); /* Houve falha na alocação de pelo menos uma área de dados, a MpE deve ser destruída. */
                        free((*pp)->vet);
                        free(*pp);
                        *pp=NULL;
                        i = M;
                        ret = FRACASSO;
                    }
            }
    }
    else
        ret = FRACASSO;
    return ret;
}

int insereNaPilha(pMP p, int nPilha, void* novo)
{

    if(p->vet==NULL)/*testa existencia da pilha*/
    {
        printf(">>Erro ao inserir, pilha inexistente\n");
        return FRACASSO;
    }

    if(p->vet[nPilha-1].descritor.topo == (p->L)-1)
    {
        printf(">>Erro ao inserir, a pilha %d está cheia\n", nPilha);
        return FRACASSO;
    }
    /*se a pilha existe e não está cheia, inserção pode ocorrer normalmente*/
    int inicioParticao = p->vet[nPilha-1].descritor.inicioParticao;
    p->vet[nPilha-1].descritor.topo += 1;
    int topo = p->vet[nPilha-1].descritor.topo;
    //printf("acrescentou topo\n");
    memcpy(p->vet[inicioParticao + topo].dados, novo, p->tamInfo);
    //int *dado = (int*)p->vet[inicioParticao + topo].dados;
    //printf("topo atual = %d\n", *dado);

    return SUCESSO;
}

int removeDaPilha(pMP p, int nPilha, void* removido)
{
    if(p->vet[nPilha-1].descritor.topo==-1)
    {
        printf(">>ERRO AO REMOVER\nA pilha %d está vazia\n", nPilha);
        return FRACASSO;
    }
    memcpy(p->vet[(p->vet[nPilha-1].descritor.topo)].dados, removido, p->tamInfo);
    p->vet[nPilha-1].descritor.topo--;
    return SUCESSO;
}

int consultaTopo(pMP p, int nPilha, void* consultado)
{
    int topo = p->vet[nPilha-1].descritor.topo;
    int inicioParticao = p->vet[nPilha-1].descritor.inicioParticao;
    if(topo == -1)
    {
        printf("\nA pilha %d esta vazia\n", nPilha);
        return FRACASSO;
    }
    memcpy(consultado, p->vet[inicioParticao + topo].dados, p->tamInfo);

    return SUCESSO;
}
