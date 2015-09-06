#include "cliente.h"



main(void)
{  
    pABB p=NULL;
    info aux, retorno,vet[]={{300,30,"Pedro"},{200,32,"Paulo"},{100,35,"Judas"},{400,31,"Manuel"},{250,33,"Lucas"},{270,32,"Andre"},        {390,34,"Thiago"},{-1,-1,'\0'}};
   unsigned int opc=1,i=0;
   if (criaABB(&p, sizeof(info)) == SUCESSO)
   {  
	 system("clear");
	 i=0;
	 do{ // carregando a ABB
            if(insereABB(p,&vet[i],comparaCamposChaves1)==SUCESSO)
	    {	printf("%i) inserido: %s, idade: %i anos, matricula: %i \n",i+1,vet[i].nome,vet[i].idade,vet[i].matricula); 
	    	i++;
	    }
	    else
       		{ puts(">>> Fracasso na inser��o");	
		  return;	
		}
	 }while(vet[i].idade>0);
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
{	tipoChave a1 = ((info *)pInfo1)->campoChave, a2 = ((info *)pInfo2)->campoChave;
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
{  tipoChave ch1 = *((tipoChave *)chave), ch2 = ((info *)pInfo)->campoChave;
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
  printf( mascaraChave,((info *)pInfo)->campoChave);

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
	info aux,retorno;
        while(1)
        { 
	 system("clear");
	 printf("\n");
	 puts("0:sair         1:inserir          2:remover             3:buscar  ");
         puts("4:reiniciar    5:perc. em ordem   6:perc. em pos-ordem  7:perc. em pre-ordem");  
	 puts("8:ABB vazia? ");
	 printf("\n:>");	
         scanf("%u",&opc);


         switch (opc)
          { case 0:
          	destroiABB(&p);
		return;
	    case 1:
          	printf("entre com matricula: ");
		flush(stdin);
          	scanf("%i", &(aux.campoChave));
                if (insereABB(p,&aux,comparaCamposChaves1)==SUCESSO)
          		puts(">>> Sucesso na inser��o");
          	else
            		puts(">>> Fracasso na inser��o");
          	break;
            case 2:
            	printf("entre com matricula: ");

          	scanf("%i", &aux.campoChave);
          	if (removeABB(p,&aux.campoChave,comparaCamposChaves2,&retorno)==SUCESSO)
          		printf(">>> Removeu: %i",retorno.campoChave);
          	else
            		puts(">>> Fracasso na remocao");
            	break;
            case 3:  
		printf("entre com matricula: ");

          	scanf("%i", &aux.campoChave);
          	if (buscaABB(p,&retorno,&aux.campoChave,comparaCamposChaves2)==SUCESSO)
			printf(">>> Buscou: %i",retorno.campoChave);
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
	
          }
	 printf("\n tecle para continuar...");
         flush(stdin);
         getchar();
       }
	return;
}
