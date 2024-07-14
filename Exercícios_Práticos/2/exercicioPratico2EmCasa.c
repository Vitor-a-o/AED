#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int MaximumGain(char* s, int x, int y);

int main(){
    char *s = "cdbcbbaaabab";
    int x = 4;
    int y = 5;

    int result = MaximumGain(s, x, y);

    printf("%d\n", result);
}

/*
================================================


    Função para calcular o score máximo
================================================
*/

int MaximumGain( char* s, int x, int y ) {
    int score = 0;
    int tamanho = strlen( s );
    char pilha[ tamanho + 1 ];
    int topo = 0;

    char c1, c2;

    if( x > y ){
        c1 = 'a';
        c2 = 'b';
    }else{
        c1 = 'b';
        c2 = 'a';
    }

    for( int i = 0; s[ i ] != '\0'; i++ ){
        if( topo > 0 && s[ i ] == c2 && pilha[ topo - 1 ] == c1 ){
            score += c1 == 'a' ? x : y;
            topo --;
        }else{
            pilha[ topo++ ] = s[ i ];
        }
    }

    char pilha2[ tamanho + 1 ];
    int topo2 = 0;
    for( int i = 0; i < topo; i++ ){
        if( topo2 > 0 && pilha[ i ] == c1 && pilha2[ topo2 - 1 ] == c2 ){
            score += c2 == 'a' ? x : y;
            topo2 --;
        }else{
            pilha2[ topo2++ ] = pilha[ i ];
        }
    }
    return score;
}