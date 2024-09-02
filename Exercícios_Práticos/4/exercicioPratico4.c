#include <stdio.h>
#include <stdlib.h>

int MaxProfitAssignment( int* difficulty, int difficultySize, int* profit, int profitSize, int* worker, int workerSize );
void PrintArray( int* arr, int size );
int* QuickSortPositions( int* arr, int* positions, int size );
int* QuickSort( int* arr, int size );
int* QuickSortPositions( int* arr, int* positions, int size );

int main(){
    int difficulty[] = { 2, 4, 6, 8, 10 };
    int profit[] = { 10, 20, 30, 40, 5 };
    int worker[] = { 4, 5, 6, 7, 2 };
    int difficultySize = 5;
    int profitSize = 5;
    int workerSize = 5;
    int maxProfit = MaxProfitAssignment( difficulty, difficultySize, profit, profitSize, worker, workerSize );
    printf( "Max profit: %d\n", maxProfit );
    return 0;

}

int MaxProfitAssignment( int* difficulty, int difficultySize, int* profit, int profitSize, int* worker, int workerSize ) {
    int maxProfit = 0;
    int profitPositions [ profitSize ];
    for( int i = 0; i < profitSize; i++ ){
        profitPositions[ i ] = i;
    }
    int* sortedProfitPositions = QuickSortPositions( profit, profitPositions, profitSize );
    int* sortedWorker = QuickSort( worker, workerSize );

    PrintArray( sortedProfitPositions, profitSize );
    PrintArray( sortedWorker, workerSize );
    PrintArray( profit, profitSize );

    //pegar o melhor trabalhador, ver se ele consegue fazer o trabalho mais rentável
    //se sim, somar o lucro, pegar o próximo trabalhador e ver se ele consegue fazer o trabalho mais rentável
    //se não, pegar o próximo trabalho mais rentável e ver se o trabalhador consegue fazer

    int i = profitSize - 1;
    int j = workerSize - 1;
    while( i >= 0 && j >= 0 ){
        printf( "Melhor Trabalhador: %d , Trabalho mais rentavel: %d \n", sortedWorker[ j ], difficulty[ sortedProfitPositions[ i ] ] );
        if( difficulty[ sortedProfitPositions[ i ] ] <= sortedWorker[ j ] ){
            maxProfit += profit[ i ];
            printf( "Lucro: %d\n", profit[ i ] );
            j--;
        } else {
            i--;
        }
    }

    return maxProfit;
}

void PrintArray( int* arr, int size ){
    for( int i = 0; i < size; i++ ){
        printf( "%d ", arr[ i ] );
    }
    printf( "\n" );
}

int* QuickSort( int* arr, int size ){
    int i, j, pivo, aux;
    if( size <= 1 ){
        return arr;
    }
    pivo = arr[ size/2 ];
    i = 0;
    j = size - 1;
    while( i <= j ){
        while( arr[ i ] < pivo ){
            i++;
        }
        while( arr[ j ] > pivo ){
            j--;
        }
        if( i <= j ){
            aux = arr[ i ];
            arr[ i ] = arr[ j ];
            arr[ j ] = aux;
            i++;
            j--;
        }
    }
    if( j > 0 ){
        QuickSort( arr, j+1 );
    }
    if( i < size ){
        QuickSort( &arr[i], size - i );
    }
    return arr;
}

int* QuickSortPositions( int* arr, int* positions, int size ){
    int i, j, pivo, aux;
    if( size <= 1 ){
        return arr;
    }
    pivo = arr[ size/2 ];
    i = 0;
    j = size - 1;
    while( i <= j ){
        while( arr[ i ] < pivo ){
            i++;
        }
        while( arr[ j ] > pivo ){
            j--;
        }
        if( i <= j ){
            aux = arr[ i ];
            arr[ i ] = arr[ j ];
            arr[ j ] = aux;
            aux = positions[ i ];
            positions[ i ] = positions[ j ];
            positions[ j ] = aux;
            i++;
            j--;
        }
    }
    if( j > 0 ){
        QuickSortPositions( arr, positions, j+1 );
    }
    if( i < size ){
        QuickSortPositions( &arr[i], &positions[i], size - i );
    }
    return positions;
}