#include "cliente.h"



main(void)
{  
    pABB p=NULL;
    Agenda aux, retorno,vet[]={{300,"Pedro","end", "fone"},{200,"Paulo","end", "fone"},{100,"Judas","end", "fone"},{400,"Manuel","end", "fone"},{250,"Lucas","end", "fone"},{270,"Andre","end", "fone"}, {390,"Thiago","end", "fone"},{0,"Thiago","end", "fone"}};
   unsigned int opc=1,i=0;
   if (criaABB(&p, sizeof(Agenda)) == SUCESSO)
   {  
	 system("clear");
	 i=0;
	 do{ // carregando a ABB
            if(insereABB(p,&vet[i],comparaCamposChaves1)==SUCESSO)
	    {	printf("%i) inserido: %d, nome: %s \n",i+1,vet[i].cod, vet[i].nome); 
	    	i++;
	    }
	    else
       		{ puts(">>> Fracasso na inser��o");	
		  return 1;	
		}
	 }while(vet[i].cod>0);
	puts("");	
	puts("tecle para continuar...");	 
	getchar();
	 menu(p);
   }
 return 1;
}

///////////////////////////////////////////////////////////////////////////////////////
/*dados os endere�os de duas instancias de registros, h� a compara��o dos
respectivos campos chaves e o retorno da rela��o entre eles: >, < ou = */
unsigned short comparaCamposChaves1(void *pInfo1, void *pInfo2)
{	tipoChave a1 = ((Agenda *)pInfo1)->cod, a2 = ((Agenda *)pInfo2)->cod;
 	if (a1 > a2)
		return '>';
	else
    		if (a1 < a2)
         		return '<';
      		else
         		return '=';
}


//////////////////////////////////////////////////////////////////////////////////////////
/*dados o endere�o do campo chave "chave" de um registro e o endere�o de uma instancia
de um registro, h� a compara��o da "chave" com o campo chave do registro e o
retorno da rela��o entre eles: >, < ou = */
unsigned short  comparaCamposChaves2(void *chave, void *pInfo)
{  tipoChave ch1 = *((int *)chave), ch2 = ((Agenda *)pInfo)->cod;
   if (ch1 > ch2)
	return '>';
   else
    	if (ch1 < ch2)
         	return '<';
       	else
         	return '=';
}

///////////////////////////////////////////////////////////
void exibeChave(void *pInfo)
{ static int i=0;
  printf( mascaraChave,((Agenda *)pInfo)->cod);

}

//////////////////////////////////////////////////////////
void flush(FILE *in)
{ int c;
  do{ c=fgetc(in);
	}while(c!='\n' && c != EOF);	
}


/////////////////////////////////////////////////////////
void menu(pABB p)
{    	unsigned int opc=1;
	Agenda aux,retorno;
        while(1)
        { 
	 system("clear");
	 printf("\n");
	 puts("0:sair         1:inserir          2:remover             3:buscar  ");
         puts("4:reiniciar    5:perc. em ordem recursivo   6:perc. em pos-ordem  7:perc. em pre-ordem");  
	 puts("8:ABB vazia?     9:perc. em ordem iterativo");
	 printf("\n:>");	
         scanf("%u",&opc);


         switch (opc)
          { case 0:
          	destroiABB(&p);
		return;
	    case 1:
          	printf("entre com codigo: ");
		flush(stdin);
          	scanf("%i", &(aux.cod));
                if (insereABB(p,&aux,comparaCamposChaves1)==SUCESSO)
          		puts(">>> Sucesso na inser��o");
          	else
            		puts(">>> Fracasso na inser��o");
          	break;
            case 2:
            	printf("entre com o codigo: ");

          	scanf("%i", &aux.cod);
          	if (removeABB(p,&aux.cod,comparaCamposChaves2,&retorno)==SUCESSO)
          		printf(">>> Removeu: %i",retorno.cod);
          	else
            		puts(">>> Fracasso na remocao");
            	break;
            case 3:  
		printf("entre com o codigo: ");

          	scanf("%i", &aux.cod);
          	if (buscaABB(p,&retorno,&aux.cod,comparaCamposChaves2)==SUCESSO)
			printf(">>> Buscou:\ncod %i\nnome %s\n",retorno.cod, retorno.nome);
		else
			puts(">>> Fracasso na busca");
		break;
            case 4:  
		reiniciaABB(p);
		puts(">>> ABB purgada!");
	 	break;
            case 5:
                if (emOrdem(p,exibeChave)==FRACASSO)
         	        puts(">>> ABB vazia");
		break;
            case 6:
                if (posOrdem(p,exibeChave)==FRACASSO)
                       puts(">>> ABB vazia");
	        break;
            case 7:
                if (preOrdem(p,exibeChave)==FRACASSO)
                      puts(">>> ABB vazia");
            	break;
            case 8:		
                if (testaVaziaABB(p)==SIM)
                       	puts(">>> ABB vazia");
                else
                	puts(">>> ABB nao vazia");
            	break;
		    case 9:
                if (emOrdemIterativa(p,exibeChave)==FRACASSO)
         	        puts(">>> ABB vazia");
		break;
	
          }
	 printf("\n tecle para continuar...");
         flush(stdin);
         getchar();
       }
	return;
}
