#include "biblioteca.h"

int main(){
	
	FILE *ptr;
	int i,j, cont,B=1,k=1;
	registro myStruct[4];
	double ti,tf,tempo;
	struct timeval tempo_inicio, tempo_fim;
	abp *pRaiz = NULL;	
	campo ***tabela;
	unsigned long long A;	
	
	while(1){
		
			
	do {
		if(B!=1)
		printf("\nValor invalido! Digite novamente.\n");		
		printf(" ______________________________________\n");
		printf("|_________________Menu_________________|\n");
		printf("| Digite [1]:Cuckoo hash               |\n");
		printf("| Digite [2]:Arvore Binaria de Pesquisa|\n");
		printf("| Digite [0]:Sair                      |\n");	
		printf("|______________________________________|\n");
		printf("\nDigite a entrada: ");
		scanf("%i",&B);
		setbuf(stdin,NULL);
	}while(B!=0 && B!=1 && B!=2);
		switch(B){

			case 1:{				
				k=1;				
				printf("\nConstruindo tabela hash....\n");
				ptr = fopen("base.bin","rb");
	
				tabela =malloc(N * sizeof(campo**));
		
				if (!ptr) {
					  printf("\nO arquivo nao pode ser aberto\n");
					  return 1;
				 }

				for (i = 0; i < N; i++){
					tabela[i] = malloc(TAM * sizeof(campo*)); 
					 for (j = 0; j < TAM; j++){
						  tabela[i][j] = NULL; //Inicializa com NULL.
					 }
				}

				i=0;
				while(i<1000000) {
					  fread(&myStruct,sizeof(registro)*4,1,ptr);
					  if(feof(ptr)!=0)
						   break;
					  // percorre os 4 registros do bloco lido e insere um por um na ABP
					  for(cont=0;cont<4;cont++) {
					  	InserirHash(tabela,myStruct[cont].naochave,i,0,0);
					}
					  i++;
				 }
		
				while(1){			
					if(k==0){		
						do{						
							if(B!=1)
								printf("Valor invalido! Digite novamente.\n");		
							printf(" ____________________________\n");
							printf("|__________Menu Hash_________|\n");
							printf("| Digite [1]:Buscar novamente|\n");
							printf("| Digite [0]:Sair            |\n");	
							printf("|____________________________|\n");
							printf("\nDigite a entrada: ");
							scanf("%i",&B);
							setbuf(stdin,NULL);	
						}while(B!=0 && B!=1);					
					}		
					switch(B){	
						
						case 1:{	
							printf("\nDigite o numero que deseja buscar: ");
							scanf("%llu",&A);
							setbuf(stdin,NULL);
							ti = tf = tempo = 0;
										
							gettimeofday(&tempo_inicio,NULL);

							PesquisarHash(tabela,A);	
	
							gettimeofday(&tempo_fim,NULL);
							tf = (double) tempo_fim.tv_usec + ((double)tempo_fim.tv_sec * (1000000.0));
							ti = (double) tempo_inicio.tv_usec + ((double)tempo_inicio.tv_sec * (1000000.0));
							tempo = (tf - ti) / 1000;
							printf("\nTempo gasto (milisegundos) para pesquisar: %lf\n", tempo);
							k=0;
							continue;
						}
					 
						case 0:{
							B=1;							
							break;
						}
					}
					printf("\nDestruindo tabela hash....\n");
					for (i = 0; i < N; i++){ 
				 		for (j = 0; j < TAM; j++)
				  			free(tabela[i][j]) ;
			 			free(tabela[i]);
					}
					free(tabela);	
					break;	
				}		
				continue;
			}	
			

			case 2:{
				B=B-1;				
				k=1;				
				printf("\nConstruindo ABP....\n");	
				ptr = fopen("base.bin","rb");
			 
				 if(!ptr){
					  printf("\nO arquivo nao pode ser aberto\n");
					  return 1;
				 }
				 
				i=0;
		
		
		
				// Cada while le um bloco de 4096 - ou seja - 4 registros
				while(i<1000000) {
					fread(&myStruct,sizeof(registro)*4,1,ptr);
						if(feof(ptr)!=0)
						   break;
					  // percorre os 4 registros do bloco lido e insere um por um na ABP
					for(cont=0;cont<4;cont++) {
				  		inserirABP(&pRaiz,myStruct[cont].naochave,i);
					}
					i++;
				}

				fclose(ptr);
				 
				 // Comeca a contar o tempo
				ti = tf = tempo = 0;
				while(1){			
					if(k==0){		
						do{	
							if(B!=1)
								printf("\nValor invalido! Digite novamente.\n");		
							printf(" ____________________________\n");
							printf("|___________Menu ABP_________|\n");
							printf("| Digite [1]:Buscar novamente|\n");
							printf("| Digite [0]:Sair            |\n");	
							printf("|____________________________|\n");
							printf("\nDigite a entrada: ");											
							scanf("%i",&B);
							setbuf(stdin,NULL);	
						}while(B!=0 && B!=1);
					}		
					switch(B){	
			
						case 1:{	
							printf("\nDigite o numero que deseja buscar: ");
							scanf("%llu",&A);
							
							gettimeofday(&tempo_inicio,NULL);
	
							// Faz a pesquisa
							PesquisarABP(pRaiz,A);
	
							// Para de contar o tempo e o imprime
							gettimeofday(&tempo_fim,NULL);
							tf = (double) tempo_fim.tv_usec + ((double)tempo_fim.tv_sec * (1000000.0));
							ti = (double) tempo_inicio.tv_usec + ((double)tempo_inicio.tv_sec * (1000000.0));
							tempo = (tf - ti) / 1000;
							printf("\nTempo gasto (milisegundos) para pesquisar: %lf\n", tempo);
							k=0;
							continue;
						}
						case 0:{							
							B=1;
							break;
						}	 

					}		
				printf("\nDestruindo ABP....\n");
				ApagaArvore(&pRaiz);	
				pRaiz = NULL;				
				break;
			}
			continue;
		}

			case 0:return 0;
		}
	}
}
