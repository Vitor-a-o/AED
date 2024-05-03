#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* longestCommonPrefix(char** strs, int strsSize);

int main(){
    char *result;
    int *strsSize;
    char **strs = {"flower","flow","flight"};
    result = longestCommonPrefix(strs, strsSize);

    printf("%d", result[0]);
    printf("%d\n", result[1]);
    
}

char* longestCommonPrefix(char** strs, int strsSize){
    char *output;

    for(int i = 0; i < strsSize; i++){
        
    }

    strsSize = 2;
    return output;
}