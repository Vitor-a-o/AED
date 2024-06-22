#include <stdio.h>
#include <stdbool.h>

bool LemonadeChange(int* bills, int billsSize);

int main(){
    char* result;
    int size = 5;
    int s[size]; 
    s[0] = 5;
    s[1] = 5;
    s[2] = 5;
    s[3] = 10;
    s[4] = 20;
    result = LemonadeChange( s, size ) ? "True" : "False";

    printf( "%s\n", result );
    
}

/*
=================================================
LemonadeChange

    Função para calcular se será possível que 
    todos os clientes de uma fila, com diferentes 
    valores de pagamento, conseguirão receber seu
    adequadamente.
=================================================
*/

bool LemonadeChange( int* bills, int billsSize ) {
    int n5 = 0, n10 = 0;
    for ( int i = 0; i < billsSize; i++ ) {
        if ( bills[i] == 20 ) {
            if ( n10 > 0 ) {
                n10--;
                if ( n5 > 0 ) {
                    n5--;
                } else {
                    return false;
                }
            } else if ( n5 > 2 ) {
                n5 -= 3;
            } else {
                return false;
            }
        } else if ( bills[i] == 10 ) {
            if ( n5 > 0 ) {
                n5--;
                n10++;
            } else {
                return false;
            }
        } else {
            n5++;
        }
    }
    return true;
}