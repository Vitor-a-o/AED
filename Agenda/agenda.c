#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//Globais

void *pBuffer;
int *menu;
int *idade;

void AdicionarPessoa();
void RemoverPessoa();
void BuscarPessoa();
void ListarPessoas();
void FreeList();
void *InitBuffer();
void MostrarMenu();
void Sair();

/*
Variaveis do Buffer
[0] *void pFirst 
[1] *void pLast
[2] *void pNew
[3] *void pAux
[6] *int menu

Pessoa
[0] *char nome
[1] *char email
[2] *int idade
[3] *void pNext
[4] *void pPrev
*/

int main(){
    pBuffer = InitBuffer();
    menu = pBuffer + sizeof(void *) * 4;
    *menu = 0;
    while( *menu != 5 ){
        MostrarMenu( pBuffer );
        switch( *menu ){
            case 1:
                AdicionarPessoa( pBuffer );
                break;
            case 2:
                RemoverPessoa( pBuffer );
                break;
            case 3:
                BuscarPessoa( pBuffer );
                break;
            case 4:
                ListarPessoas( pBuffer );
                break;
            case 5:
                Sair( pBuffer );
                break;
        }
    }
    return 0;
}

void MostrarMenu(){
    printf( "===============================\n" );
    printf( "| Para adicionar pessoa ( 1 ) |\n" );
    printf( "| Para remover pessoa   ( 2 ) |\n" );
    printf( "| Para buscar pessoa    ( 3 ) |\n" );
    printf( "| Para listar pessoas   ( 4 ) |\n" );
    printf( "| Para sair             ( 5 ) |\n" );
    printf( "===============================\n" );
    scanf( "%d", menu );
    fflush( stdin );
    return;
}

void *InitBuffer(){
    void *pBuffer = malloc( sizeof( void * ) * 4 + sizeof( int ) );
    if ( pBuffer == NULL ) {
        perror( "Falha ao alocar memória para o buffer" );
        exit( EXIT_FAILURE );
    }

    ( ( void ** )pBuffer )[ 0 ] = NULL; //pFirst
    ( ( void ** )pBuffer )[ 1 ] = NULL; //pLast
    ( ( void ** )pBuffer )[ 2 ] = NULL; //pNew
    ( ( void ** )pBuffer )[ 3 ] = NULL; //pAux

    return pBuffer;
}

void AdicionarPessoa(){

    ( ( void ** )pBuffer )[ 2 ] = malloc( sizeof( void * ) * 2 + sizeof( char ) * 100 + sizeof( int ) );

    if ( ( ( void ** )pBuffer )[ 2 ] == NULL ) {
        perror( "Falha ao alocar memória para nodo" );
        exit( EXIT_FAILURE );
    }

    ( ( void ** )( ( void ** )pBuffer )[ 2 ] )[ 0 ] = NULL; //next
    ( ( void ** )( ( void ** )pBuffer )[ 2 ] )[ 1 ] = NULL; //prev
    idade = ( ( void ** )pBuffer )[ 2 ] + sizeof( void * ) * 2 + sizeof( char ) * 100; //idade
    *idade = 0;

    printf( "Nome: \n" );
    scanf( "%s", ( ( char ** )pBuffer )[ 2 ] + sizeof(void *) * 2 ); //nome
    fflush( stdin );
    printf( "\nEmail: \n" );
    scanf( "%s", ( ( char ** )pBuffer )[ 2 ] + sizeof(void *) * 2 + sizeof( char ) * 50 ); //email
    fflush( stdin );
    printf( "\nIdade: \n" );
    scanf( "%d", idade );
    fflush( stdin );

    printf("\n");
    printf( "Pessoa adicionada\n" );
    printf("Nome: %s\n", ( ( char ** )pBuffer )[ 2 ] + sizeof(void *) * 2 );
    printf("Email: %s\n", ( ( char ** )pBuffer )[ 2 ] + sizeof(void *) * 2 + sizeof( char ) * 50 );
    printf("Idade: %d\n", *idade );
    printf("\n");

    if ( ( ( void ** )pBuffer )[ 0 ] == NULL ){ // Se não existir nenhum elemento
        ( ( void ** )pBuffer )[ 1 ] = ( ( void ** )pBuffer )[ 0 ] = ( ( void ** )pBuffer )[ 2 ];
        return;
    }else{
        ( ( void ** )pBuffer )[ 3 ] = ( ( void ** )pBuffer )[ 1 ];

        while( ( ( void ** )pBuffer )[ 3 ] != NULL && strcasecmp( ( ( char ** )pBuffer )[ 2 ] + sizeof(void *) * 2, ( ( char ** )pBuffer )[ 3 ] + sizeof(void *) * 2 ) <= 0 ){
            ( ( void ** )pBuffer )[ 3 ] = ( ( void ** )( ( void ** )pBuffer )[ 3 ] )[ 1 ];
        }

        if( ( ( void ** )pBuffer )[ 3 ] == NULL ){ // Inserir no inicio
            ( ( void ** )( ( void ** )pBuffer )[ 2 ] )[ 0 ] = ( ( void ** )pBuffer )[ 0 ];
            ( ( void ** )( ( void ** )pBuffer )[ 0 ] )[ 1 ] = ( ( void ** )pBuffer )[ 2 ];
            ( ( void ** )pBuffer )[ 0 ] = ( ( void ** )pBuffer )[ 2 ];
        }else if( ( ( void ** )pBuffer )[ 3 ] == ( ( void ** )pBuffer )[ 1 ] ){ // Inserir no fim
            ( ( void ** )( ( void ** )pBuffer )[ 1 ] )[ 0 ] = ( ( void ** )pBuffer )[ 2 ];
            ( ( void ** )( ( void ** )pBuffer )[ 2 ] )[ 1 ] = ( ( void ** )pBuffer )[ 1 ];
            ( ( void ** )pBuffer )[ 1 ] = ( ( void ** )pBuffer )[ 2 ]; 
        }else{ // Inserir no meio (entre Aux e Aux->next)
            ( ( void ** )( ( void ** )pBuffer )[ 2 ] )[ 0 ] = ( ( void ** )( ( void ** )pBuffer )[ 3 ] )[ 0 ];
            ( ( void ** )( ( void ** )pBuffer )[ 2 ] )[ 1 ] = ( ( void ** )pBuffer )[ 3 ];
            ( ( void ** )( ( void ** )( ( void ** )pBuffer )[ 3 ] )[ 0 ] )[ 1 ] = ( ( void ** )pBuffer )[ 2 ];
            ( ( void ** )( ( void ** )pBuffer )[ 3 ] )[ 0 ] = ( ( void ** )pBuffer )[ 2 ];
        }
    }
    return;
}

void RemoverPessoa(){
    if( ( ( void ** )pBuffer )[ 0 ] == NULL ){
        printf( "Agenda vazia\n" );
        return;
    }

    ( ( void ** )pBuffer )[ 3 ] = ( ( void ** )pBuffer )[ 0 ];
    idade = ( ( void ** )pBuffer )[ 3 ] + sizeof( void * ) * 2 + sizeof( char ) * 100;

    printf( "Pessoa removida\n" );
    printf("Nome: %s\n", ( ( char ** )pBuffer )[ 3 ] + sizeof(void *) * 2 );
    printf("Email: %s\n", ( ( char ** )pBuffer )[ 3 ] + sizeof(void *) * 2 + sizeof( char ) * 50 );
    printf("Idade: %d\n", *idade );
    printf("\n");

    ( ( void ** )pBuffer )[ 0 ] = ( ( void ** )( ( void ** )pBuffer )[ 0 ] )[ 0 ];

    if( ( ( void ** )pBuffer )[ 0 ] == NULL ){
        ( ( void ** )pBuffer )[ 1 ] = NULL;
    }else{
        ( ( void ** )( ( void ** )pBuffer )[ 0 ] )[ 1 ] = NULL;
    }
    free( ( ( void ** )pBuffer )[ 3 ] );
    return;
}

void BuscarPessoa(){
    if( ( ( void ** )pBuffer )[ 0 ] == NULL ){
        printf( "Agenda vazia\n" );
        return;
    }

    ( ( void ** )pBuffer )[ 2 ] = malloc(sizeof( char ) * 50 );

    printf( "Nome: \n" );
    scanf( "%s", ( ( char ** )pBuffer )[ 2 ] );
    fflush( stdin );
    printf( "\n" );

    ( ( void ** )pBuffer )[ 3 ] = ( ( void ** )pBuffer )[ 0 ];

    while( ( ( void ** )pBuffer )[ 3 ] != NULL && strcasecmp( ( ( char ** )pBuffer )[ 2 ], ( ( char ** )pBuffer )[ 3 ] + sizeof( void * ) * 2 ) != 0 ){
        ( ( void ** )pBuffer )[ 3 ] = ( ( void ** )( ( void ** )pBuffer )[ 3 ] )[ 0 ];
    }

    free( ( ( void ** )pBuffer )[ 2 ] );

    if( ( ( void ** )pBuffer )[ 3 ] == NULL ){
        printf( "Pessoa nao encontrada\n" );
        return;
    }

    idade = ( ( void ** )pBuffer )[ 3 ] + sizeof( void * ) * 2 + sizeof( char ) * 100;

    printf( "Pessoa encontrada\n" );
    printf("Nome: %s\n", ( ( char ** )pBuffer )[ 3 ] + sizeof(void *) * 2 );
    printf("Email: %s\n", ( ( char ** )pBuffer )[ 3 ] + sizeof(void *) * 2 + sizeof( char ) * 50 );
    printf("Idade: %d\n", *idade );
    printf("\n");
    return;
}

void ListarPessoas(){
    ( ( void ** )pBuffer )[ 3 ] = ( ( void ** )pBuffer )[ 0 ];
    printf( "Pessoas:\n" );
    while( ( ( void ** )pBuffer )[ 3 ] != NULL ){
        idade = ( ( void ** )pBuffer )[ 3 ] + sizeof( void * ) * 2 + sizeof( char ) * 100;
        printf("Nome: %s\n", ( ( char ** )pBuffer )[ 3 ] + sizeof(void *) * 2 );
        printf("Email: %s\n", ( ( char ** )pBuffer )[ 3 ] + sizeof(void *) * 2 + sizeof( char ) * 50 );
        printf("Idade: %d\n", *idade );
        printf("\n");
        ( ( void ** )pBuffer )[ 3 ] = ( ( void ** )( ( void ** )pBuffer )[ 3 ] )[ 0 ];
    }
    return;
}

void FreeList(){
    ( ( void ** )pBuffer )[ 3 ] = ( ( void ** )pBuffer )[ 0 ];
    while( ( ( void ** )pBuffer )[ 3 ] != NULL ){
        ( ( void ** )pBuffer )[ 2 ] = ( ( void ** )( ( void ** )pBuffer )[ 3 ] )[ 0 ];
        free( ( ( void ** )pBuffer )[ 3 ] );
        ( ( void ** )pBuffer )[ 3 ] = ( ( void ** )pBuffer )[ 2 ];
    }
    return;
}

void Sair(){
    FreeList( pBuffer );
    free( ( ( void ** )pBuffer )[ 2 ] );
    free( ( ( void ** )pBuffer )[ 3 ] );
    free( pBuffer );
    exit( EXIT_SUCCESS );
}

