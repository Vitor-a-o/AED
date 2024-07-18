#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void AdicionarPessoa( void *pBuffer );
void RemoverPessoa( void *pBuffer );
void BuscarPessoa( void *pBuffer );
void ListarPessoas( void *pBuffer );
void FreeList( void *pBuffer );
void *InitBuffer();
void MostrarMenu( void *pBuffer );
void Sair( void *pBuffer );

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
    void *pBuffer = InitBuffer();
    while( *( ( int * )( ( void ** )pBuffer )[ 6 ] ) != 5 ){
        MostrarMenu( pBuffer );
        switch( *( ( int * )( ( void ** )pBuffer )[ 6 ] ) ){
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

void MostrarMenu( void *pBuffer ){
    printf( "===============================\n" );
    printf( "| Para adicionar pessoa ( 1 ) |\n" );
    printf( "| Para remover pessoa   ( 2 ) |\n" );
    printf( "| Para buscar pessoa    ( 3 ) |\n" );
    printf( "| Para listar pessoas   ( 4 ) |\n" );
    printf( "| Para sair             ( 5 ) |\n" );
    printf( "===============================\n" );
    scanf( "%d", ( ( int * )( ( void ** )pBuffer )[ 6 ] ) );
    fflush( stdin );
    return;
}

void *InitBuffer(){
    void *pBuffer = malloc( sizeof(void *) * 7 );
    if ( pBuffer == NULL ) {
        perror( "Falha ao alocar memória para o buffer" );
        exit( EXIT_FAILURE );
    }

    ( ( void ** )pBuffer )[ 0 ] = NULL; //pFirst
    ( ( void ** )pBuffer )[ 1 ] = NULL; //pLast
    ( ( void ** )pBuffer )[ 2 ] = NULL; //pNew
    ( ( void ** )pBuffer )[ 3 ] = NULL; //pAux
    ( ( void ** )pBuffer )[ 6 ] = malloc( sizeof( int ) );
    *( ( int * )( ( void ** )pBuffer )[ 6 ] ) = 0; //menu

    if( ( ( void ** )pBuffer )[ 6 ] == NULL ){
        perror( "Falha ao alocar memória para int menu" );
        exit( EXIT_FAILURE );
    }

    return pBuffer;
}

void AdicionarPessoa( void *pBuffer ){

    ( ( void ** )pBuffer )[ 2 ] = malloc( sizeof(void *) * 5 );

    if ( ( ( void ** )pBuffer )[ 2 ] == NULL) {
        perror( "Falha ao alocar memória para nodo" );
        exit( EXIT_FAILURE );
    }

    ( ( void ** )( ( void ** )pBuffer )[ 2 ] )[ 0 ] = malloc( sizeof( char ) * 30 ); //nome
    ( ( void ** )( ( void ** )pBuffer )[ 2 ] )[ 1 ] = malloc( sizeof( char ) * 30 ); //email

    if ( ( ( void ** )( ( void ** )pBuffer )[ 2 ] )[ 0 ] == NULL || ( ( void ** )( ( void ** )pBuffer )[ 2 ] )[ 1 ] == NULL ) {
        perror("Falha ao alocar memória para nome e email");
        exit(EXIT_FAILURE);
    }

    ( ( void ** )( ( void ** )pBuffer )[ 2 ] )[ 2 ] = malloc( sizeof( int ) ); //idade

    if ( ( ( void ** )( ( void ** )pBuffer )[ 2 ] )[ 2 ] == NULL ) {
        perror("Falha ao alocar memória para idade");
        exit(EXIT_FAILURE);
    }

    printf( "Nome: \n" );
    scanf( "%s", ( char * )( ( void ** )( ( void ** )pBuffer )[ 2 ] )[ 0 ] );
    fflush( stdin );
    printf( "\nEmail: \n" );
    scanf( "%s", ( char * )( ( void ** )( ( void ** )pBuffer )[ 2 ] )[ 1 ] );
    fflush( stdin );
    printf( "\nIdade: \n" );
    scanf( "%d", ( int * )( ( void ** )( ( void ** )pBuffer )[ 2 ] )[ 2 ] );
    fflush( stdin );

    printf("\n");
    printf( "Pessoa adicionada\n" );
    printf("Nome: %s\n", ( char * )( ( void ** )( ( void ** )pBuffer )[ 2 ] )[ 0 ] );
    printf("Email: %s\n", ( char * )( ( void ** )( ( void ** )pBuffer )[ 2 ] )[ 1 ]);
    printf("Idade: %d\n", *( ( int * )( ( void ** )( ( void ** )pBuffer )[ 2 ] )[ 2 ] ));
    printf("\n");

    ( ( void ** )( ( void ** )pBuffer )[ 2 ] )[ 3 ] = NULL; //next
    ( ( void ** )( ( void ** )pBuffer )[ 2 ] )[ 4 ] = NULL; //prev

    if ( ( ( void ** )pBuffer )[ 0 ] == NULL ){ // Se não existir nenhum elemento
        ( ( void ** )pBuffer )[ 1 ] = ( ( void ** )pBuffer )[ 0 ] = ( ( void ** )pBuffer )[ 2 ];
        return;
    }else{
        ( ( void ** )pBuffer )[ 3 ] = ( ( void ** )pBuffer )[ 1 ];

        while( ( ( void ** )pBuffer )[ 3 ] != NULL && strcmp( ( char * )( ( void ** )( ( void ** )pBuffer )[ 2 ] )[ 0 ], ( char * )( ( void ** )( ( void ** )pBuffer )[ 3 ] )[ 0 ] ) <= 0 ){
            ( ( void ** )pBuffer )[ 3 ] = ( ( void ** )( ( void ** )pBuffer )[ 3 ] )[ 4 ];
        }

        if( ( ( void ** )pBuffer )[ 3 ] == NULL ){ // Inserir no inicio
            ( ( void ** )( ( void ** )pBuffer )[ 2 ] )[ 3 ] = ( ( void ** )pBuffer )[ 0 ];
            ( ( void ** )( ( void ** )pBuffer )[ 0 ] )[ 4 ] = ( ( void ** )pBuffer )[ 2 ];
            ( ( void ** )pBuffer )[ 0 ] = ( ( void ** )pBuffer )[ 2 ];
        }else if( ( ( void ** )pBuffer )[ 3 ] == ( ( void ** )pBuffer )[ 1 ] ){ // Inserir no fim
            ( ( void ** )( ( void ** )pBuffer )[ 1 ] )[ 3 ] = ( ( void ** )pBuffer )[ 2 ];
            ( ( void ** )( ( void ** )pBuffer )[ 2 ] )[ 4 ] = ( ( void ** )pBuffer )[ 1 ];
            ( ( void ** )pBuffer )[ 1 ] = ( ( void ** )pBuffer )[ 2 ]; 
        }else{ // Inserir no meio (entre Aux e Aux->next)
            ( ( void ** )( ( void ** )pBuffer )[ 2 ] )[ 3 ] = ( ( void ** )( ( void ** )pBuffer )[ 3 ] )[ 3 ];
            ( ( void ** )( ( void ** )pBuffer )[ 2 ] )[ 4 ] = ( ( void ** )pBuffer )[ 3 ];
            ( ( void ** )( ( void ** )( ( void ** )pBuffer )[ 3 ] )[ 3 ] )[ 4 ] = ( ( void ** )pBuffer )[ 2 ];
            ( ( void ** )( ( void ** )pBuffer )[ 3 ] )[ 3 ] = ( ( void ** )pBuffer )[ 2 ];
        }
    }
    return;
}

void RemoverPessoa( void *pBuffer ){
    if( ( ( void ** )pBuffer )[ 0 ] == NULL ){
        printf( "Agenda vazia\n" );
        return;
    }
    ( ( void ** )pBuffer )[ 3 ] = ( ( void ** )pBuffer )[ 0 ];

    printf( "Pessoa removida\n" );
    printf("Nome: %s\n", ( char * )( ( void ** )( ( void ** )pBuffer )[ 3 ] )[ 0 ] );
    printf("Email: %s\n", ( char * )( ( void ** )( ( void ** )pBuffer )[ 3 ] )[ 1 ] );
    printf("Idade: %d\n", *( ( int * )( ( void ** )( ( void ** )pBuffer )[ 3 ] )[ 2 ] ) );
    printf("\n");

    ( ( void ** )pBuffer )[ 0 ] = ( ( void ** )( ( void ** )pBuffer )[ 0 ] )[ 3 ];

    if( ( ( void ** )pBuffer )[ 0 ] == NULL ){
        ( ( void ** )pBuffer )[ 1 ] = NULL;
    }else{
        ( ( void ** )( ( void ** )pBuffer )[ 0 ] )[ 4 ] = NULL;
    }
    free(( ( void ** )( ( void ** )pBuffer )[ 3 ] )[ 0 ]);
    free(( ( void ** )( ( void ** )pBuffer )[ 3 ] )[ 1 ]);
    free(( ( void ** )( ( void ** )pBuffer )[ 3 ] )[ 2 ]);
    free( ( ( void ** )pBuffer )[ 3 ] );
    return;
}

void BuscarPessoa( void *pBuffer ){
    if( ( ( void ** )pBuffer )[ 0 ] == NULL ){
        printf( "Agenda vazia\n" );
        return;
    }
    ( ( void ** )pBuffer )[ 3 ] = ( ( void ** )pBuffer )[ 0 ];
    printf( "Pessoa encontrada\n" );
    printf("Nome: %s\n", ( char * )( ( void ** )( ( void ** )pBuffer )[ 3 ] )[ 0 ] );
    printf("Email: %s\n", ( char * )( ( void ** )( ( void ** )pBuffer )[ 3 ] )[ 1 ] );
    printf("Idade: %d\n", *( ( int * )( ( void ** )( ( void ** )pBuffer )[ 3 ] )[ 2 ] ) );
    printf("\n");
    return;
}

void ListarPessoas( void *pBuffer ){
    ( ( void ** )pBuffer )[ 3 ] = ( ( void ** )pBuffer )[ 0 ];
    printf( "Pessoas:\n" );
    while( ( ( void ** )pBuffer )[ 3 ] != NULL ){
        printf("Nome: %s\n", ( char * )( ( void ** )( ( void ** )pBuffer )[ 3 ] )[ 0 ] );
        printf("Email: %s\n", ( char * )( ( void ** )( ( void ** )pBuffer )[ 3 ] )[ 1 ] );
        printf("Idade: %d\n", *( ( int * )( ( void ** )( ( void ** )pBuffer )[ 3 ] )[ 2 ] ) );
        printf("\n");
        ( ( void ** )pBuffer )[ 3 ] = ( ( void ** )( ( void ** )pBuffer )[ 3 ] )[ 3 ];
    }
    return;
}

void FreeList( void *pBuffer ){
    ( ( void ** )pBuffer )[ 3 ] = ( ( void ** )pBuffer )[ 0 ];
    while( ( ( void ** )pBuffer )[ 3 ] != NULL ){
        ( ( void ** )pBuffer )[ 2 ] = ( ( void ** )( ( void ** )pBuffer )[ 3 ] )[ 3 ];
        free(( ( void ** )( ( void ** )pBuffer )[ 3 ] )[ 0 ]);
        free(( ( void ** )( ( void ** )pBuffer )[ 3 ] )[ 1 ]);
        free(( ( void ** )( ( void ** )pBuffer )[ 3 ] )[ 2 ]);
        free( ( ( void ** )pBuffer )[ 3 ] );
        ( ( void ** )pBuffer )[ 3 ] = ( ( void ** )pBuffer )[ 2 ];
    }
    return;
}

void Sair( void *pBuffer ){
    FreeList( pBuffer );
    free( ( ( void ** )pBuffer )[ 6 ] );
    free( ( ( void ** )pBuffer )[ 2 ] );
    free( ( ( void ** )pBuffer )[ 3 ] );
    free( pBuffer );
    exit( EXIT_SUCCESS );
}

