#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    struct Nodo *pFirst;
    int tamanho;
}Lista;

typedef struct{
    char c;
    struct Nodo *pNext;
}Nodo;

int maximumGain(char* s, int x, int y);
void PUSH( Lista *pLista, char c );

int main(){
    char *s = "aabbaaxybbaabb";
    int x = 5;
    int y = 4;

    int result = maximumGain(s, x, y);
}

int maximumGain( char* s, int x, int y ) {
    int score = 0;
    int tamanho = strlen(s);
    printf("%d\n", tamanho);
    Lista *pString;

    pString->pFirst = NULL;
    pString->tamanho = 0;

    //Listando a String
    for(int i = 0; i < tamanho; i++){
        PUSH(pString, s[i]);
    }

    Nodo *iNodo;
    Nodo *jNodo;

    char c1, c2;

    if( x > y ){
        c1 = 'a';
        c2 = 'b';
    }else{
        c1 = 'b';
        c2 = 'a';
    }

    bool p1, p2;

    do{        //Laço para percorrer a Lista
        for( iNodo = pString->pFirst, jNodo = iNodo->pNext; jNodo != NULL; iNodo = jNodo, jNodo = iNodo->pNext ){
            while( iNodo->c == c1 && jNodo->c == c2 ){
                p1 = true;
                free(iNodo);
                iNodo = jNodo->pNext;
                free(jNodo);
                jNodo = iNodo->pNext;
                pString->tamanho -= 2;
            }
        }
        if( !p1 ){
            for( iNodo = pString->pFirst, jNodo = iNodo->pNext; jNodo != NULL; iNodo = jNodo, jNodo = iNodo->pNext ){
                while( iNodo->c == c2 && jNodo->c == c1 ){
                    p2 = true;
                    free(iNodo);
                    iNodo = jNodo->pNext;
                    free(jNodo);
                    jNodo = iNodo->pNext;
                    pString->tamanho -= 2;
                }
            }
        }
    }while(p1 && p2);
}

void PUSH( Lista *pLista, char c ){
    Nodo *pNovo;
    pNovo = ( Nodo* )malloc(sizeof( Nodo ));
    if(pNovo == NULL){
        printf("Erro ao alocar memoria!\n");
        return;
    }
    pNovo->c = c;
    pNovo->pNext = pLista->pFirst;
    pLista->pFirst = pNovo;

    pLista->tamanho++;
}