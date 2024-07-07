#include <stdio.h>
#include <string.h>

void AddNome(char *nomes);
void RemNome(char *nomes);
void List(char *nomes);
void Sair(void);

int main(){
    int menu;
    char *nomes = "";

    printf("Escolha uma ação: \n");
    printf("(1) Adicionar nome \n");
    printf("(2) Remover nome \n");
    printf("(3) Listar nomes \n");
    printf("(4) Sair \n");

    scanf( "%d\n", &menu );

    do{
        switch( menu ){
            case( 1 ):
            AddNome( nomes );
            break;
            
            case( 2 ):
            RemNome( nomes );
            break;

            case( 3 ):
            List( nomes );
            break;

            case( 4 ):
            Sair();
            break; 
        }
    }while( menu != 1 || menu != 2 || menu != 3 || menu != 4 );
    
}

void AddNome( char * nomes ){
    char *novoNome;
    char separador = "-";

    printf("Digite o nome a ser adicionado: \n");
    fgets(novoNome, sizeof(novoNome), stdin);
    strcat(nomes, novoNome);
    strncat(nomes, separador, 1);
}

void RemNome(char * nomes){
    char nomeRem[30];
    char separador = '-';
    char *nomeCmp = "";
    int tamanho = strlen(nomes);

    printf("Digite o nome a ser adicionado: \n");
    fgets(nomeRem, sizeof(nomeRem), stdin);

    int i = 0, j = 0;
    do{
        memset(nomeCmp, 0, sizeof(nomeCmp));
        j = i;
        while(nomes[i] != separador){
            nomeCmp[i] = nomes[i];
            i++;
        }
        nomeCmp[i] = '\0';

    }while(strcmp(nomeCmp, nomeRem) != 0);

    int tamNome = strlen(nomeCmp);

    while(i < tamanho){
        
    } 
}

