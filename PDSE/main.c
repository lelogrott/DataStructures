#include "PDSE.h"

void mostraInt(void *reg)
{
    printf(">>%d\n", *((int*)(reg)));
}

int main(){
    pPDSE pilha;
    
    cria(&pilha, sizeof(int));
    
    int opc, novo, consultado, removido, nElementos;
    
    do{
        printf("1. inserir matricula\n2. remover matricula\n3. consultar topo\n4. mostrar pilha\n5. inverter pilha\n6. criar pilha sequencial\n0. sair\n\n> ");
        scanf("%d", &opc);
        
        switch(opc){
            clrscr();
            case 1:
                printf("\nDigite a matricula:\n> ");
                scanf("%d", &novo);
                if(insere(pilha,&novo)==SUCESSO)
                    printf("\nsucesso na insercao!\n");
                getchar();getchar();
                clrscr();
                break;
            case 2:
                if(removeTopo(pilha, &removido)==SUCESSO){
                    printf("\nELEMENTO REMOVIDO:\n-------------------\n%d\n-------------------\n", removido);
                    printf("\nsucesso na remocao!\n");
                }
                getchar();getchar();
                clrscr();
                break;
            case 3:
                if(busca(pilha, &consultado)==SUCESSO){
                    printf("\nTOPO ATUAL:\n-------------------\n%d\n-------------------\n", consultado);
                    printf("\nsucesso na consulta!\n");
                }
                getchar();getchar();
                clrscr();
                break;
            case 4:
                mostraPilha(pilha, mostraInt);
                getchar();getchar();
                clrscr();
                break;
            case 5:
                inverte(pilha);
                printf("\nsucesso na inversao!\n");
                getchar();getchar();
                clrscr();
                break;
            case 6:
                printf("\nDigite a quantidade de elementos da pilha:\n>");
                scanf("%d", &nElementos);
                geraPilha(pilha, nElementos);
                printf("\nsucesso na criacao!\n");
                getchar();getchar();
                clrscr();
                break;
            case 0:
                destroi(&pilha);
                break;
        }
    }while(opc!=0);
    
    return 0;
    
}


    
