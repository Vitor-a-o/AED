#include <stdio.h>
#include <stdbool.h>

typedef struct Lista{
    Nodo *pFirst;
    int tamanho;
}Lista;

typedef struct Nodo{
    Conteudo *info;
    Nodo *pNext;
}Nodo;

typedef struct Conteudo{
    int cod;
    char nome[40];
    float preco;
}Conteudo;

void PUSH( Lista *pLista, Conteudo *pConteudo ){
    Nodo *pNovo;
    pNovo = ( Nodo* )malloc(sizeof( Nodo ));
    if(pNovo == NULL){
        printf("Erro ao alocar memoria!\n");
        return;
    }
    pNovo->info = pConteudo;
    pNovo->pNext = pLista->pFirst;
    pLista->pFirst = pNovo;

    pLista->tamanho++;
}

bool POP( Lista *pLista ){
    if( isEmpty(pLista) ){
        printf("Lista vazia!\n");
        return 0;
    }

    Nodo *pNodo = pLista->pFirst;
    Conteudo *pCont = pLista->pFirst->info;
    printf( "Conteudo apagado\n  Codigo: %d\n Nome: %s\n Preco: %.2f\n", pCont->cod, pCont->nome, pCont->preco );
    pLista->pFirst = pLista->pFirst->pNext;

    free( pNodo );
    pLista->tamanho--;
    return 1;
}

void imprimeLista( Lista *pLista ){
    Nodo *pNodo;

    if( isEmpty( pLista ) ){
        printf( "Lista vazia!\n" );
    } else {
        for(pNodo = pLista->pFirst; pNodo != NULL; pNodo = pNodo->pNext)
            printf( "Conteudo apagado\n  Codigo: %d\n Nome: %s\n Preco: %.2f\n",
            pNodo->info->cod,
            pNodo->info->nome,
            pNodo->info->preco );
    }
}

bool isEmpty( Lista *pLista ){
    return pLista->pFirst == NULL;
}

void clear( Lista *pLista ){
    while(!isEmpty(pLista)){
        POP(pLista);
    }
    pLista->tamanho = 0;
}

void reset( Lista *pLista ){
    clear(pLista);
    pLista->pFirst = NULL;
}