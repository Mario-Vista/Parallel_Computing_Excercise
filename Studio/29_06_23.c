/**
 * PROVA SCRITTA LABORATORIO TRACCIA 1: 29-06-2023
 * 
 * Implementare un programma parallelo per l'ambiente multicore 
 * con np unità processanti che impieghi la libreria OpenMP.
 * 
 * Il programma deve essere organizzato come segue:
 * 
 * 1. Ogni core deve generare una matrice A di dimensione N/np x M,
 *    mentre solo il core master deve leggere un vettore b di lunghezza M
 * 
 * 2. Tutti i core devono calcolare localmente il prodotto c = A x b
 * 
 * 3. Quindi, i core devono organizzarsi per determinare il massimo
 *    valore tra tutti gli elementi dei vettori locali c e il massimo 
 *    globale tra tutti i vettori locali c
 * 
 * 4. Infine, il core master deve stampare il valore massimo
 *    globale trovato ed il tempo d'esecuzione.
*/

//librerie
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>


void fillMatrix( int***, int, int );
void printMatrix( int**, int, int, char[] );
void printVector( int*, int, char[] );

int main()
{
    srand(time(NULL));
    int **A;    //matrice A
    int **C;    //matrice dei vettori locali
    int N, np, M;   //size per la matrice A e il vettore b;
    int *b;  //vettore
    int i,j;
    double startTime, endTime;

    //prendo le variabili in input
    printf("Inserisci il valore di N: ");
    scanf("%d", &N);

    printf("\nInserisci il valore di np: ");
    scanf("%d", &np);

    printf("\nInserisci il valore di M: ");
    scanf("%d", &M);

    int row = N/np;

    //setto il numero di unità processanti
    omp_set_num_threads(np);

    //Allocazione matrici A e C
    #pragma omp master
    {
        A = (int **)calloc(N, sizeof(int *));
        C = (int **)calloc(np, sizeof(int *));

    }

    startTime = omp_get_wtime();
    #pragma omp parallel for
    for(i = 0; i < N; i++)
    {
        A[i] = (int *) calloc(M, sizeof(int));
        C[i] = (int *) calloc(M, sizeof(int));
    }


    #pragma omp master
    {
        // il core master deve leggere un vettore b di lunghezza M
        b = ( int* ) calloc( M, sizeof( int ) );
       
        for ( i = 0; i < M; i++ )
        {
            b[i] = rand() % 20 + 1;
        }
           
            fillMatrix( &A, N, M );
            printMatrix( A, N, M, "Matrix A" );
            printVector( b, M, "Vector B" );
              
    } 
    
    // * 2. Tutti i core devono calcolare localmente il prodotto c = A x b

    #pragma omp parallel for
    for(int i  = 0; i < row; i++)
    {
        for(int j = 0; j < M; j++)
        {
            C[omp_get_thread_num()][j] = A[i][j]*b[j];
        }
    }

/* 3. Quindi, i core devono organizzarsi per determinare il massimo
 *    valore tra tutti gli elementi dei vettori locali c e il massimo 
 *    globale tra tutti i vettori locali c
*/

int max, localmax,id;

#pragma omp parallel private(localmax, id) shared(max, C)
{
    localmax = 0;
    id = omp_get_thread_num();
    for(int j = 0; j < M; j++)
    {
        if(localmax < C[id][j])
        {
            localmax = C[id][j];
        }

        #pragma omp barrier

        if(localmax > max)
        {
            max = localmax;
        }

    }
}

/*
 * 4. Infine, il core master deve stampare il valore massimo
 *    globale trovato ed il tempo d'esecuzione.
*/

#pragma omp master
{
    endTime = omp_get_wtime();
    printf("Il valore massimo trovato è: %d, e il tempo totale di esecuzione è %ld", max, endTime-startTime);

}



    return 0;
}




void fillMatrix( int*** matrix, int N, int M ) {
    for ( int i = 0; i < N; i++ )
        for ( int j = 0; j < M; j++ )
            ( *matrix )[i][j] = rand() % 20 + 1;
}

void printMatrix( int** matrix, int N, int M, char name[] ) {
    printf( "\n%s:\n", name );
    for ( int i = 0; i < N; i++ ) {
        for ( int j = 0; j < M; j++ )
            printf( "%d    ", matrix[i][j] );
        printf( "\n" );
    }
}

void printVector( int* vector, int n, char name[] ) {
    printf( "\n%s: ", name );
    for ( int i = 0; i < n; i++ )
        printf( "%d ", vector[i] );
    printf( "\n" );
}
