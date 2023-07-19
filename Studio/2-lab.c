/**
 * PROVA SCRITTA LABORATORIO TRACCIA 2: 29-06-2023
 * 
 * Implementare un programma parallelo per l'ambiente multicore 
 * con np unità processanti che impieghi la libreria OpenMP.
 * 
 * Il programma deve essere organizzato come segue:
 * 
 * 1. il master thread deve generare una matrice A,
 *    e leggere uno scalare alpha
 * 
 * 2. i core thread devono effettuare l’operazione B = A + alpha
 * 
 * 3. i core thread devono effettuare la trasposta di B
 * 
 * 4. i core thread dovevano stampare la loro porzione
 *    (quella che hanno trasposto) e il master thread
 *    doveva stampare il tempo di esecuzione
*/


#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

// Costante utilizzata per il riempimento
// della matrice con numeri casuali
#define MAXVALUE 9

void allocationMatrix( int***, int, int );
void fillMatrix( int***, int, int );
void printMatrix( int**, int, int, char[] );
void deallocationMatrix( int***, int );
int main() {

    int i, j; // Indici
    double startTime, endTime;  //variabili per tracciare i tempi

    int** matrixA;  // Matrice A
    int **matrixB;  //Matrice B
    int **matrixC;  //trasposta di B
    int N, M;       // Size della matrice

    int np;         //numero di unità processanti
    int alpha;      //scalare

    // Come seme per la generazioni di numeri
    // pseudo-casuali utilizzo l'orario corrente
    srand( time( NULL ) );

    // Tempo di inizio
    startTime = omp_get_wtime();

/*
 * 1. il master thread deve generare una matrice A,
 *    e leggere uno scalare alpha
*/ 
    #pragma omp master
    {
        //allocazione della matrice
        printf( "\nEnter row of matrix N: " );
        scanf( "%d", &N );
        printf( "\nEnter column of matrix N: " );
        scanf( "%d", &M );
        allocationMatrix( &matrixA, N, M );
        allocationMatrix(&matrixB, N,M);
        allocationMatrix(&matrixC, M, N);
        fillMatrix( &matrixA, N, M );
        printMatrix( matrixA, N, M, "Matrix A" );

        //lettura dello scalare
        printf("Inserisci il valore dello scalare alpha: ");
        scanf("%d", &alpha);

        printf("Inserisci il numero di unità processanti: ");
        scanf("%d", &np);   
    }

    omp_set_num_threads(np);

/*
* 2. i core thread devono effettuare l’operazione B = A + alpha
*/

#pragma omp parallel for shared(N,M,matrixA,matrixB,alpha) private(i,j)
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < M; j++)
        {
            matrixB[i][j] = matrixA[i][j] + alpha;
        }
    }

/*
 * 3. i core thread devono effettuare la trasposta di B
*/

    #pragma omp parallel for shared(N,M,matrixC,matrixB,) private(i,j)
    for(i = 0; i < N;i++)
    {
        for(j = 0; j < M; j++)
        {
            matrixC[j][i] = matrixB[i][j];
        }
    }


/*
 * 4. i core thread dovevano stampare la loro porzione
 *    (quella che hanno trasposto) e il master thread
 *    doveva stampare il tempo di esecuzione
*/

#pragma omp parallel for private(i,j) shared(N,M,matrixC)
for(i = 0; i < N; i++)
{
    printf("Thread %d trasponde:", omp_get_thread_num());
    for(j = 0; j < M; j++)
    {
        printf("%d ", matrixC[j][i]);
    }
    printf("\n");

}


    #pragma omp master
    {
        // Tempo di fine
        endTime = omp_get_wtime();
        // Il master thread doveva stampare il tempo di esecuzione
        printf( "\nTempo di esecuzione: %lf", endTime - startTime );
    }


    printf( "\n" );
    
    deallocationMatrix( &matrixA, N );

    return 0;
}






/**
 * Procedura utilizzata per l'allocazione della matrice
 * 
 * @param matrix matrice da allocare
 * @param N righe della matrice
 * @param M colonne della matrcie
*/
void allocationMatrix( int*** matrix, int N, int M ) {
    *matrix = ( int** ) calloc( N, sizeof( int* ) );
    for ( int i = 0; i < N; i++ )
        ( *matrix )[i] = ( int* ) calloc( M, sizeof( int ) );
}

/**
 * Procedura utilizzata per il riempimento della matrice
 * 
 * @param matrix matrice da allocare
 * @param N righe della matrice
 * @param M colonne della matrcie
*/
void fillMatrix( int*** matrix, int N, int M ) {
    for ( int i = 0; i < N; i++ )
        for ( int j = 0; j < M; j++ )
            ( *matrix )[i][j] = rand() % MAXVALUE + 1;
}

/**
 * Procedura utilizzata per la stampa della matrice
 * 
 * @param matrix matrice da allocare
 * @param N righe della matrice
 * @param M colonne della matrcie
 * @param name nome della matrice
*/
void printMatrix( int** matrix, int N, int M, char name[] ) {
    printf( "\n%s:\n", name );
    for ( int i = 0; i < N; i++ ) {
        for ( int j = 0; j < M; j++ )
            printf( "%d    ", matrix[i][j] );
        printf( "\n" );
    }
}

/**
 * Procedura utilizzata per la deallocazione della matrice
 * 
 * @param matrix matrice da allocare
 * @param N righe della matrice
*/
void deallocationMatrix( int*** matrix, int N ) {
    for ( int i = 0; i < N; i++ )
        free( ( *matrix )[i] );
    free( *matrix );
}