#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isValid(char* s);
bool match(char close, char open);

int main(){
    char* result;
    char* s = "()[]{}";
    result = isValid(s) ? "True" : "False";

    printf("%s\n", result);
}

bool isValid(char* s) {
    int tamanho = strlen(s);
    char pilha[tamanho];
    int j = -1;
    if( tamanho == 1 ){
        return false;
    }

    for( int i = 0; s[i] != '\0'; i++ ){
        if( s[i] == '(' || s[i] == '[' || s[i] == '{' ){
            pilha[j+1] = s[i];
            j++;
        } else if( j >= 0) {
            if( match(s[i], pilha[j]) ){
                j--;
            } else {
                return false;
            }
        } else{
            return false;
        }
    }
    if( j >= 0 ){
        return false;
    } else {
        return true;
    }
}

bool match( char close ,char open ) {
    
    return (close == ')' && open == '(') || (close == ']' && open == '[') || (close == '}' && open == '{');
}
