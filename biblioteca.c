#include "biblioteca.h"


void inserirABP(abp **pRaiz, unsigned long long valor, unsigned int bloco) {
	
   if (*pRaiz == NULL) {
       *pRaiz = malloc(sizeof(abp));
       (*pRaiz)->esq = NULL;
       (*pRaiz)->dir = NULL;
       (*pRaiz)->naochave = valor;
       (*pRaiz)->lista = malloc(sizeof(no));
       (*pRaiz)->lista->prox = NULL;
       (*pRaiz)->lista->bloco = bloco;
   } else {
       if(valor < (*pRaiz)->naochave) {
           inserirABP(&(*pRaiz)->esq, valor,bloco);
        }
       if(valor > (*pRaiz)->naochave) {
           inserirABP(&(*pRaiz)->dir, valor,bloco);
        }
        if(valor == (*pRaiz)->naochave) {
        	no *no = (*pRaiz)->lista;
        	while(no->prox != NULL) {
        		no = no->prox;
			}
			
			struct no *novo = malloc(sizeof(*no));
			novo->prox = NULL;
			novo->bloco = bloco;
			no->prox = novo;
		}
   }
}

void PesquisarABP(abp *pRaiz, unsigned long long valor) {
   if(pRaiz != NULL) {
   		// Caso tenha encontrado o valor CHAVE
   		if (pRaiz->naochave == valor) {
   			// Abre o arquivo para ler os dados dos valores CHAVE
			FILE *ptr;
			int i;
			registro dados[4];
			int bloco,auxbloco=0;
			ptr = fopen("base.bin","rb");
   			// Percorre a lista que contem esses valores como CHAVE
   			no *aux = pRaiz->lista;
   			while(aux != NULL) {
					auxbloco=0;					
					bloco = aux->bloco;   				
					if(bloco>500000){
						auxbloco=bloco-500000;
						bloco=bloco-auxbloco;
					}		
					if(fseek(ptr, bloco*4096 , SEEK_SET) == 0){//COLOCA O CABEÇOTE NO BLOCO QUE ESTA O REGISTRO 
						if(bloco!=0)
							if(fseek(ptr, auxbloco*4096 , SEEK_CUR) == 0)
   					// Le o bloco do HD na posicao do bloco e armazena no vetor dados
   					fread(&dados,sizeof(registro)*4, 1 ,ptr);
   					// Percorre o vetor de dados do bloco
		   			for(i=0;i<4;i++) {
		   			// Quando encontrar um valor do vetor com o naochave igual -> imprime todos os dados do registro
		   				if (dados[i].naochave == valor) {
		   					printf("\nChave: %llu",dados[i].chave);
								printf("\nNaoChave: %llu",dados[i].naochave);
								printf("\nOutros: %s",dados[i].outros);
								printf("\n");		
							}
						}
					}								
					aux = aux->prox;
				}
			fclose(ptr);
   			return;
		}
   		if(pRaiz->naochave > valor) {
   				return PesquisarABP(pRaiz->esq,valor);
		} else {
				return PesquisarABP(pRaiz->dir,valor);
		}
   }
   printf("\n\nValor Chave Nao Encontrado!!\n");
	return;
}
void ApagaArvore (abp **raiz) {
	if ((*raiz) != NULL){
	ApagaArvore (&(*raiz)->esq) ; 
	ApagaArvore (&(*raiz)->dir) ;
  	free(*raiz);
  	}
}

int hash(int funcao, unsigned long long chave){//FUNÇÕES DO CUCKOO HASH  
	if(chave<0)//CASO O VALOR SEJA NEGATIVO TIRA O MODULO PARA ACHAR O INDICE
		chave=chave*-1;    
	switch (funcao){
     	case 0: return (chave/337)%TAM;						/*RETORNA O INDICE*/
      case 1: return (chave/10003)%TAM;
		case 2: return (chave/11)%TAM;
      case 3: return (chave/23)%TAM;    
		case 4: return (chave/17)%TAM;
		case 5: return (chave/TAM)%TAM;
 		case 6: return chave%TAM;   	
	}
}


void PesquisarHash(campo*** tabela, unsigned long long naochave) {
	int i, indice,bloco,j,cont=0,auxbloco=0;	
	FILE *ptr;
	registro dados[4];
	ptr = fopen("base.bin","rb");
	
	for(i=0;i<N;i++){//BUSCA O ELEMENTO EM TODOS OS INDICES DO MESMO
		auxbloco=0;		
		indice=hash(i,naochave);
		if(tabela[i][indice]!=NULL){					  //CASO TENHA ALGUM ELEMENTO 		
			if(tabela[i][indice]->naochave==naochave)//VERIFICA SE O ELEMENTO DESEJADO
				bloco=tabela[i][indice]->bloco;		  //SE FOR, GUARDAMOS O VALOR DO BLOCO
			else//CASO NÃO SEJA O ELEMENTO DESEJADO
				continue;
		}else//CASO NÃO TENHA NENHUM ELEMENTO NA POSICÃO 
			continue;	
		if(bloco>500000){
			auxbloco=bloco-500000;
			bloco=bloco-auxbloco;
		}		
		if(fseek(ptr, bloco*4096 , SEEK_SET) == 0){//COLOCA O CABEÇOTE NO BLOCO QUE ESTA O REGISTRO 
			if(bloco!=0)
				if(fseek(ptr, auxbloco*4096 , SEEK_CUR) == 0){
			fread(&dados,sizeof(registro), 4 ,ptr);// LE O BLOCO QUE CONTEM O REGISTRO
				for(j=0;j<4;j++) {// PERCORRE O VETOR DE DADOS DO BLOCO
					if (dados[j].naochave == naochave) {// QUANDO ENCONTRAR UM VALOR DO VETOR COM O NAOCHAVE IGUAL -> IMPRIME TODOS OS	DADOS DO REGISTRO
						printf("\nChave: %llu",dados[j].chave);
						printf("\nNaoChave: %llu",dados[j].naochave);
						printf("\nOutros: %s",dados[j].outros);
						printf("\n");		
						cont++;												
					}	
				}
			}
		}	
	}
	if(cont==0)
		printf("\n\nValor Chave Nao Encontrado!!\n");
	return;
}
void InserirHash(campo*** tabela,unsigned long long naochave, int bloco, int funcao,int rehash){		
	if(rehash<10000){//CASO NÃO CONSIGA INSERIR NA TABELA(LOOP INFINITO "REHASH")		
		
	int indice=hash(funcao,naochave);//JOGA O VALOR NAOCHAVE NA FUNÇÃO HASH	
		
		if(tabela[funcao][indice]==NULL){						//VERIFICA SE NÃO TEM NADA NA POSIÇÃO,
			tabela[funcao][indice]=malloc(sizeof(campo));	//CASO NÃO TENHA ALOCA NO INDICE O ELEMENTO
			tabela[funcao][indice]->naochave=naochave;
			tabela[funcao][indice]->bloco=bloco;
			return;	
		
		}else{															//TEM ELEMENTO NA POSIÇÃO
			campo *aux=tabela[funcao][indice];					//GUARDA ELE EM UM AUX
			tabela[funcao][indice]=malloc(sizeof(campo));	//ALOCA O ELEMENTO NA POSIÇÃO DO INDICE
			tabela[funcao][indice]->naochave=naochave;		//COLOCA O VALOR NÃOCHAVE
			tabela[funcao][indice]->bloco=bloco;				//COLOCA O BLOCO DO REGISTRO QUE POSSUI O VALOR NAOCHAVE
			funcao=(funcao+1)%N;										//PASSA PRA PROXIMA TABELA
			rehash++;														
			return InserirHash(tabela, aux->naochave, aux->bloco, funcao,rehash);//JOGA O ELEMENTO DO AUX PARA TENTAR INSERIR NA PROXIMA TABELA
		}
	}	
	printf("rehash\n");
	return;
}
