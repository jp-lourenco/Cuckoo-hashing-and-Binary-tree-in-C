#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

#define N 7//NUMEROS DE FUNCÕES E TABELAS QUE O CHUCKOO HASH IMPLEMENTADO POSSUI 
#define TAM 720059	//TAMANHO DAS TABELAS
#define _FILE_OFFSET_BITS 64

typedef struct registro {
	unsigned long long chave; // 8 bytes
	unsigned long long naochave; // 8 bytes
	unsigned char outros[1008]; // 1008 bytes
} registro;

typedef struct no {
	unsigned int bloco;
	struct no *prox;
} no;

typedef struct abp {
	unsigned long long naochave;
	struct abp *esq, *dir;
	struct no *lista;
} abp;

typedef struct campo {
	unsigned long long naochave;
	int bloco;
} campo;

void inserirABP(abp **pRaiz, unsigned long long valor, unsigned int bloco);

void PesquisarABP(abp *pRaiz, unsigned long long valor);

void ApagaArvore (abp **raiz);

int hash(int funcao, unsigned long long chave);

void PesquisarHash(campo*** tabela, unsigned long long naochave);

void InserirHash(campo*** tabela,unsigned long long naochave, int bloco, int funcao,int rehash);

#endif