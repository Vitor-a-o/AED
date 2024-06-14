#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* longestCommonPrefix(char** strs, int strsSize);

int main(){
    char *result;
    int strsSize = 3;
    char *strs[] = {"dog","dacecar","dar"};
    result = longestCommonPrefix(strs, strsSize);
    printf("%s\n", result);
    free(result);
    return 0;
}

char* longestCommonPrefix( char** strs, int strsSize ){
    if (strsSize == 0) return "";
    if (strsSize == 1) return strs[0];

    char *output;
    output = (char *)malloc(strlen(strs[0]) + 1);
    if(output != NULL){
        output[0] = '\0'; 
        int i = 0;
        while( 1 ){
            for(int j = 0;j < strsSize-1; j++){
                if(strs[j][i] != strs[j+1][i] || strs[j][i] == '\0'){
                    return output;
                }
            }
            char novoChar[2] = {strs[0][i], '\0'};
            strcat(output, novoChar);
            i++;
        }
    }else{
        printf("Nao foi encontrada memoria!");
    }
    return 0;
}