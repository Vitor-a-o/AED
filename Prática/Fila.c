#include <stdio.h>
#include <stdbool.h>

typedef struct Fila{
    Nodo *pFirst;
    Nodo *pLast;
    int tamanho;
}Fila;

typedef struct Nodo{
    Conteudo *info;
    Nodo *pNext;
}Nodo;

typedef struct Conteudo{
    int cod;
    char nome[40];
    float preco;
}Conteudo;

void PUSH( Fila *pFila, Conteudo *pConteudo ){
    Nodo *pNovo;
    pNovo = ( Nodo* )malloc(sizeof( Nodo ));
    if(pNovo == NULL){
        printf("Erro ao alocar memoria!\n");
        return;
    }
    pNovo->info = pConteudo;
    pNovo->pNext = NULL;

    if(pFila->pLast != NULL){
        pFila->pLast->pNext = pNovo;
    }else{
        pFila->pFirst = pNovo;
    }

    pFila->pLast = pNovo;
    pFila->tamanho++;
}

bool POP( Fila *pFila ){
    if(isEmpty(pFila)){
        printf("Fila vazia!\n");
        return 0;
    }

    Nodo *pNodo = pFila->pFirst;
    Conteudo *pCont = pFila->pFirst->info;
    printf( "Conteudo apagado\n  Codigo: %d\n Nome: %s\n Preco: %.2f\n", pCont->cod, pCont->nome, pCont->preco );
    pFila->pFirst = pFila->pFirst->pNext;

    if( pFila->pFirst == NULL ){
        pFila->pLast = NULL;
    }

    free( pNodo );
    pFila->tamanho--;
    return 1;
}

void imprimeFila( Fila *pFila ){
    Nodo *pNodo;

    if( pFila->pFirst == NULL ){
        printf("Fila vazia!\n");
    }else{
        for(pNodo = pFila->pFirst; pNodo != NULL; pNodo = pNodo->pNext)
            printf( "Conteudo apagado\n  Codigo: %d\n Nome: %s\n Preco: %.2f\n",
            pNodo->info->cod,
            pNodo->info->nome,
            pNodo->info->preco );
    }
}

bool isEmpty( Fila *pFila ){
    return pFila->pFirst == NULL;
}

void clear( Fila *pFila ){
    while(!isEmpty(pFila)){
        POP(pFila);
    }
    pFila->tamanho = 0;
}

void reset( Fila *pFila ){
    clear(pFila);
    pFila->pFirst = NULL;
    pFila->pLast = NULL;
}