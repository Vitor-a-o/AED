#include <stdio.h>
#include <stdbool.h>

typedef struct Pilha{
    Nodo *pFirst;
    int tamanho;
}Pilha;

typedef struct Nodo{
    Conteudo *info;
    Nodo *pNext;
}Nodo;

typedef struct Conteudo{
    int cod;
    char nome[40];
    float preco;
}Conteudo;

void PUSH( Pilha *pPilha, Conteudo *pConteudo ){
    Nodo *pNovo;
    pNovo = ( Nodo* )malloc(sizeof( Nodo ));
    if(pNovo == NULL){
        printf("Erro ao alocar memoria!\n");
        return;
    }
    pNovo->info = pConteudo;
    pNovo->pNext = pPilha->pFirst;
    pPilha->pFirst = pNovo;

    pPilha->tamanho++;
}

bool POP( Pilha *pPilha ){
    if( isEmpty(pPilha) ){
        printf("Pilha vazia!\n");
        return 0;
    }

    Nodo *pNodo = pPilha->pFirst;
    Conteudo *pCont = pPilha->pFirst->info;
    printf( "Conteudo apagado\n  Codigo: %d\n Nome: %s\n Preco: %.2f\n", pCont->cod, pCont->nome, pCont->preco );
    pPilha->pFirst = pPilha->pFirst->pNext;

    free( pNodo );
    pPilha->tamanho--;
    return 1;
}

void imprimeFila( Pilha *pPilha ){
    Nodo *pNodo;

    if( isEmpty( pPilha ) ){
        printf( "Fila vazia!\n" );
    } else {
        for(pNodo = pPilha->pFirst; pNodo != NULL; pNodo = pNodo->pNext)
            printf( "Conteudo apagado\n  Codigo: %d\n Nome: %s\n Preco: %.2f\n",
            pNodo->info->cod,
            pNodo->info->nome,
            pNodo->info->preco );
    }
}

bool isEmpty( Pilha *pPilha ){
    return pPilha->pFirst == NULL;
}

void clear( Pilha *pPilha ){
    while(!isEmpty(pPilha)){
        POP(pPilha);
    }
    pPilha->tamanho = 0;
}

void reset( Pilha *pPilha ){
    clear(pPilha);
    pPilha->pFirst = NULL;
}